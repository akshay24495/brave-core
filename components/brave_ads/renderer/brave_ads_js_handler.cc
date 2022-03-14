/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/renderer/brave_ads_js_handler.h"

#include <utility>

#include "base/json/json_writer.h"
#include "base/no_destructor.h"
#include "base/values.h"
#include "content/public/renderer/render_frame.h"
#include "content/public/renderer/v8_value_converter.h"
#include "gin/arguments.h"
#include "gin/function_template.h"
#include "third_party/blink/public/common/browser_interface_broker_proxy.h"
#include "third_party/blink/public/common/thread_safe_browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/web_string.h"
#include "third_party/blink/public/web/blink.h"
#include "third_party/blink/public/web/web_console_message.h"
#include "third_party/blink/public/web/web_local_frame.h"
#include "third_party/blink/public/web/web_script_source.h"

namespace brave_ads {

namespace {

constexpr char kBraveRequestAdsEnabledApi[] = "braveRequestAdsEnabled";

constexpr char kRequestAdsEnabledUserGestureRejectReason[] =
    "braveRequestAdsEnabled: API can only be initiated by a user gesture.";

constexpr char kBraveSendSearchAdConfirmationApi[] =
    "braveSendSearchAdConfirmation";

constexpr char kViewedConfirmation[] = "viewed";

constexpr char kClickedConfirmation[] = "clicked";

constexpr char kSendSearchAdConfirmationWrongConfirmationType[] =
    "braveSendSearchAdConfirmation: Wrong confirmation type.";

constexpr char kSendSearchAdConfirmationAdAttributesIsNotAnObject[] =
    "braveSendSearchAdConfirmation: At attributes is not an object.";

constexpr char kSendSearchAdConfirmationUserGestureRejectReason[] =
    "braveSendSearchAdConfirmation: Clicked confirmation can only be initiated "
    "by a user gesture.";

}  // namespace

BraveAdsJSHandler::BraveAdsJSHandler(content::RenderFrame* render_frame)
    : render_frame_(render_frame) {}

BraveAdsJSHandler::~BraveAdsJSHandler() = default;

void BraveAdsJSHandler::AddBraveRequestAdsEnabledFunction(
    v8::Local<v8::Context> context) {
  AddJavaScriptObjectToFrame(
      context, kBraveRequestAdsEnabledApi,
      base::BindRepeating(&BraveAdsJSHandler::RequestAdsEnabled,
                          base::Unretained(this)));
}

void BraveAdsJSHandler::AddBraveSendSearchAdConfirmationFunction(
    v8::Local<v8::Context> context) {
  AddJavaScriptObjectToFrame(
      context, kBraveSendSearchAdConfirmationApi,
      base::BindRepeating(&BraveAdsJSHandler::SendSearchAdConfirmation,
                          base::Unretained(this)));
}

template <typename Sig>
void BraveAdsJSHandler::AddJavaScriptObjectToFrame(
    v8::Local<v8::Context> context,
    const std::string& name,
    const base::RepeatingCallback<Sig>& callback) {
  v8::Isolate* isolate = blink::MainThreadIsolate();
  v8::HandleScope handle_scope(isolate);
  if (context.IsEmpty()) {
    return;
  }
  v8::Context::Scope context_scope(context);

  v8::Local<v8::Object> global = context->Global();
  v8::Local<v8::Object> chrome_obj;
  v8::Local<v8::Value> chrome_value;
  if (!global->Get(context, gin::StringToV8(isolate, "chrome"))
           .ToLocal(&chrome_value) ||
      !chrome_value->IsObject()) {
    chrome_obj = v8::Object::New(isolate);
    global->Set(context, gin::StringToSymbol(isolate, "chrome"), chrome_obj)
        .Check();
  } else {
    chrome_obj = chrome_value->ToObject(context).ToLocalChecked();
  }

  BindFunctionToObject(isolate, chrome_obj, name, callback);
}

template <typename Sig>
void BraveAdsJSHandler::BindFunctionToObject(
    v8::Isolate* isolate,
    v8::Local<v8::Object> javascript_object,
    const std::string& name,
    const base::RepeatingCallback<Sig>& callback) {
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  javascript_object
      ->Set(context, gin::StringToSymbol(isolate, name),
            gin::CreateFunctionTemplate(isolate, callback)
                ->GetFunction(context)
                .ToLocalChecked())
      .Check();
}

bool BraveAdsJSHandler::EnsureConnected() {
  if (!brave_ads_.is_bound()) {
    render_frame_->GetBrowserInterfaceBroker()->GetInterface(
        brave_ads_.BindNewPipeAndPassReceiver());
    brave_ads_.set_disconnect_handler(base::BindOnce(
        &BraveAdsJSHandler::OnRemoteDisconnect, base::Unretained(this)));
  }

  return brave_ads_.is_bound();
}

void BraveAdsJSHandler::OnRemoteDisconnect() {
  brave_ads_.reset();
  EnsureConnected();
}

v8::Local<v8::Promise> BraveAdsJSHandler::RequestAdsEnabled(
    v8::Isolate* isolate) {
  if (!EnsureConnected()) {
    return v8::Local<v8::Promise>();
  }

  v8::MaybeLocal<v8::Promise::Resolver> maybe_resolver =
      v8::Promise::Resolver::New(isolate->GetCurrentContext());
  if (maybe_resolver.IsEmpty()) {
    return v8::Local<v8::Promise>();
  }

  v8::Local<v8::Promise::Resolver> resolver = maybe_resolver.ToLocalChecked();

  auto* web_frame = render_frame_->GetWebFrame();
  DCHECK(web_frame);
  if (!web_frame->HasTransientUserActivation()) {
    v8::Local<v8::String> result =
        v8::String::NewFromUtf8(isolate,
                                kRequestAdsEnabledUserGestureRejectReason)
            .ToLocalChecked();
    ALLOW_UNUSED_LOCAL(resolver->Reject(isolate->GetCurrentContext(), result));
    return resolver->GetPromise();
  }

  auto promise_resolver = std::make_unique<v8::Global<v8::Promise::Resolver>>();
  promise_resolver->Reset(isolate, resolver);
  auto context_old = std::make_unique<v8::Global<v8::Context>>(
      isolate, isolate->GetCurrentContext());
  brave_ads_->RequestAdsEnabled(base::BindOnce(
      &BraveAdsJSHandler::OnBooleanResponse, base::Unretained(this),
      std::move(promise_resolver), isolate, std::move(context_old)));

  return resolver->GetPromise();
}

v8::Local<v8::Promise> BraveAdsJSHandler::SendSearchAdConfirmation(
    v8::Isolate* isolate,
    std::string confirmation_type,
    v8::Local<v8::Value> ad_attributes) {
  if (!EnsureConnected()) {
    return v8::Local<v8::Promise>();
  }

  v8::MaybeLocal<v8::Promise::Resolver> maybe_resolver =
      v8::Promise::Resolver::New(isolate->GetCurrentContext());
  if (maybe_resolver.IsEmpty()) {
    return v8::Local<v8::Promise>();
  }

  v8::Local<v8::Promise::Resolver> resolver = maybe_resolver.ToLocalChecked();

  if (!ad_attributes->IsObject()) {
    v8::Local<v8::String> result =
        v8::String::NewFromUtf8(
            isolate, kSendSearchAdConfirmationAdAttributesIsNotAnObject)
            .ToLocalChecked();
    ALLOW_UNUSED_LOCAL(resolver->Reject(isolate->GetCurrentContext(), result));
    return resolver->GetPromise();
  }

  std::unique_ptr<base::Value> ad_attributes_value =
      content::V8ValueConverter::Create()->FromV8Value(
          ad_attributes, isolate->GetCurrentContext());

  std::string ad_attributes_json;
  if (!base::JSONWriter::Write(*ad_attributes_value, &ad_attributes_json)) {
    return v8::Local<v8::Promise>();
  }

  if (confirmation_type != kViewedConfirmation &&
      confirmation_type != kClickedConfirmation) {
    v8::Local<v8::String> result =
        v8::String::NewFromUtf8(isolate,
                                kSendSearchAdConfirmationWrongConfirmationType)
            .ToLocalChecked();
    ALLOW_UNUSED_LOCAL(resolver->Reject(isolate->GetCurrentContext(), result));
    return resolver->GetPromise();
  }

  if (confirmation_type == kClickedConfirmation) {
    auto* web_frame = render_frame_->GetWebFrame();
    DCHECK(web_frame);
    if (!web_frame->HasTransientUserActivation()) {
      v8::Local<v8::String> result =
          v8::String::NewFromUtf8(
              isolate, kSendSearchAdConfirmationUserGestureRejectReason)
              .ToLocalChecked();
      ALLOW_UNUSED_LOCAL(
          resolver->Reject(isolate->GetCurrentContext(), result));
      return resolver->GetPromise();
    }
  }

  auto promise_resolver = std::make_unique<v8::Global<v8::Promise::Resolver>>();
  promise_resolver->Reset(isolate, resolver);
  auto context_old = std::make_unique<v8::Global<v8::Context>>(
      isolate, isolate->GetCurrentContext());
  brave_ads_->SendSearchAdConfirmation(
      confirmation_type, ad_attributes_json,
      base::BindOnce(&BraveAdsJSHandler::OnBooleanResponse,
                     base::Unretained(this), std::move(promise_resolver),
                     isolate, std::move(context_old)));

  return resolver->GetPromise();
}

void BraveAdsJSHandler::OnBooleanResponse(
    std::unique_ptr<v8::Global<v8::Promise::Resolver>> promise_resolver,
    v8::Isolate* isolate,
    std::unique_ptr<v8::Global<v8::Context>> context_old,
    bool response) {
  v8::HandleScope handle_scope(isolate);
  v8::Local<v8::Context> context = context_old->Get(isolate);
  v8::Context::Scope context_scope(context);
  v8::MicrotasksScope microtasks(isolate,
                                 v8::MicrotasksScope::kDoNotRunMicrotasks);

  v8::Local<v8::Promise::Resolver> resolver = promise_resolver->Get(isolate);
  v8::Local<v8::Boolean> result = v8::Boolean::New(isolate, response);

  ALLOW_UNUSED_LOCAL(resolver->Resolve(context, result));
}

}  // namespace brave_ads
