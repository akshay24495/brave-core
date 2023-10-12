/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/legacy_migration/rewards/legacy_rewards_migration_transaction_history_json_reader.h"

#include "base/json/json_reader.h"
#include "base/values.h"
#include "brave/components/brave_ads/core/internal/legacy_migration/rewards/legacy_rewards_migration_transaction_history_json_reader_util.h"

namespace brave_ads::rewards::json::reader {

absl::optional<TransactionList> ReadTransactionHistory(
    const std::string& json) {
  const absl::optional<base::Value::Dict> dict =
      base::JSONReader::ReadDict(json);
  if (!dict) {
    return absl::nullopt;
  }

  return ParseTransactionHistory(*dict);
}

}  // namespace brave_ads::rewards::json::reader
