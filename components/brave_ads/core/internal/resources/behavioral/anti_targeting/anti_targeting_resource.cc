/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/resources/behavioral/anti_targeting/anti_targeting_resource.h"

#include <utility>

#include "base/functional/bind.h"
#include "brave/components/brave_ads/common/pref_names.h"
#include "brave/components/brave_ads/core/internal/account/account_util.h"
#include "brave/components/brave_ads/core/internal/ads_client_helper.h"
#include "brave/components/brave_ads/core/internal/common/logging_util.h"
#include "brave/components/brave_ads/core/internal/resources/behavioral/anti_targeting/anti_targeting_feature.h"
#include "brave/components/brave_ads/core/internal/resources/behavioral/anti_targeting/anti_targeting_resource_constants.h"
#include "brave/components/brave_ads/core/internal/resources/country_components.h"
#include "brave/components/brave_ads/core/internal/resources/resources_util_impl.h"
#include "brave/components/brave_news/common/pref_names.h"

namespace brave_ads {

namespace {

bool DoesRequireResource() {
  return UserHasOptedIn();
}

}  // namespace

AntiTargetingResource::AntiTargetingResource() {
  AdsClientHelper::AddObserver(this);
}

AntiTargetingResource::~AntiTargetingResource() {
  AdsClientHelper::RemoveObserver(this);
}

///////////////////////////////////////////////////////////////////////////////

void AntiTargetingResource::MaybeLoad() {
  if (DoesRequireResource()) {
    Load();
  }
}

void AntiTargetingResource::MaybeLoadOrReset() {
  DidLoad() ? MaybeReset() : MaybeLoad();
}

void AntiTargetingResource::Load() {
  did_load_ = true;

  LoadAndParseResource(kAntiTargetingResourceId,
                       kAntiTargetingResourceVersion.Get(),
                       base::BindOnce(&AntiTargetingResource::LoadCallback,
                                      weak_factory_.GetWeakPtr()));
}

void AntiTargetingResource::LoadCallback(
    ResourceParsingErrorOr<AntiTargetingInfo> result) {
  if (!result.has_value()) {
    return BLOG(0, "Failed to initialize " << kAntiTargetingResourceId
                                           << " anti-targeting resource ("
                                           << result.error() << ")");
  }

  if (result.value().version == 0) {
    return BLOG(7, kAntiTargetingResourceId
                       << " anti-targeting resource is not available");
  }

  BLOG(1, "Successfully loaded " << kAntiTargetingResourceId
                                 << " anti-targeting resource");

  anti_targeting_ = std::move(result).value();

  BLOG(1, "Successfully initialized " << kAntiTargetingResourceId
                                      << " anti-targeting resource version "
                                      << kAntiTargetingResourceVersion.Get());
}

void AntiTargetingResource::MaybeReset() {
  if (DidLoad() && !DoesRequireResource()) {
    Reset();
  }
}

void AntiTargetingResource::Reset() {
  BLOG(1, "Reset anti-targeting resource");
  anti_targeting_.reset();
  did_load_ = false;
}

void AntiTargetingResource::OnNotifyLocaleDidChange(
    const std::string& /*locale*/) {
  MaybeLoad();
}

void AntiTargetingResource::OnNotifyPrefDidChange(const std::string& path) {
  if (path == prefs::kEnabled || path == brave_news::prefs::kBraveNewsOptedIn ||
      path == brave_news::prefs::kNewTabPageShowToday) {
    MaybeLoadOrReset();
  }
}

void AntiTargetingResource::OnNotifyDidUpdateResourceComponent(
    const std::string& id) {
  if (IsValidCountryComponentId(id)) {
    MaybeLoad();
  }
}

}  // namespace brave_ads
