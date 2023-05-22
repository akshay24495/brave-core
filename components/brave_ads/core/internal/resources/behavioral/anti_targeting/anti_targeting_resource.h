/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_RESOURCES_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_RESOURCE_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_RESOURCES_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_RESOURCE_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "brave/components/brave_ads/core/ads_client_notifier_observer.h"
#include "brave/components/brave_ads/core/internal/resources/behavioral/anti_targeting/anti_targeting_info.h"
#include "brave/components/brave_ads/core/internal/resources/resource_parsing_error_or.h"
#include "third_party/abseil-cpp/absl/types/optional.h"

namespace brave_ads {

class AntiTargetingResource final : public AdsClientNotifierObserver {
 public:
  AntiTargetingResource();

  AntiTargetingResource(const AntiTargetingResource&) = delete;
  AntiTargetingResource& operator=(const AntiTargetingResource&) = delete;

  AntiTargetingResource(AntiTargetingResource&&) noexcept = delete;
  AntiTargetingResource& operator=(AntiTargetingResource&&) noexcept = delete;

  ~AntiTargetingResource() override;

  bool IsInitialized() const { return static_cast<bool>(anti_targeting_); }

  const absl::optional<AntiTargetingInfo>& get() const {
    return anti_targeting_;
  }

 private:
  void MaybeLoad();
  void MaybeLoadOrReset();

  bool DidLoad() const { return did_load_; }
  void Load();
  void LoadCallback(ResourceParsingErrorOr<AntiTargetingInfo> result);

  void MaybeReset();
  void Reset();

  // AdsClientNotifierObserver:
  void OnNotifyLocaleDidChange(const std::string& locale) override;
  void OnNotifyPrefDidChange(const std::string& path) override;
  void OnNotifyDidUpdateResourceComponent(const std::string& id) override;

  absl::optional<AntiTargetingInfo> anti_targeting_;

  bool did_load_ = false;

  base::WeakPtrFactory<AntiTargetingResource> weak_factory_{this};
};

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CORE_INTERNAL_RESOURCES_BEHAVIORAL_ANTI_TARGETING_ANTI_TARGETING_RESOURCE_H_
