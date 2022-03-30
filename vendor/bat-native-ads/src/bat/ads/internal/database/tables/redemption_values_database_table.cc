/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/database/tables/redemption_values_database_table.h"

#include <algorithm>
#include <functional>
#include <utility>

#include "base/check.h"
#include "base/strings/stringprintf.h"
#include "bat/ads/ads_client.h"
#include "bat/ads/internal/ads_client_helper.h"
#include "bat/ads/internal/database/database_statement_util.h"
#include "bat/ads/internal/database/database_table_util.h"
#include "bat/ads/internal/database/database_util.h"

namespace ads {
namespace database {
namespace table {

namespace {

constexpr char kTableName[] = "redemption_values";

int BindParameters(mojom::DBCommand* command,
                   const CreativeAdList& creative_ads) {
  DCHECK(command);

  int count = 0;

  int index = 0;
  for (const auto& creative_ad : creative_ads) {
    BindString(command, index++, creative_ad.creative_instance_id);
    BindDouble(command, index++, creative_ad.value);

    count++;
  }

  return count;
}

void BindParameters(mojom::DBCommand* command,
                    const std::string& creative_instance_id,
                    const double value) {
  DCHECK(command);
  DCHECK(!creative_instance_id.empty());

  BindString(command, 0, creative_instance_id);
  BindDouble(command, 1, value);
}

}  // namespace

RedemptionValues::RedemptionValues() = default;

RedemptionValues::~RedemptionValues() = default;

void RedemptionValues::InsertOrUpdate(mojom::DBTransaction* transaction,
                                      const CreativeAdList& creative_ads) {
  DCHECK(transaction);

  if (creative_ads.empty()) {
    return;
  }

  mojom::DBCommandPtr command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::RUN;
  command->command = BuildInsertOrUpdateQuery(command.get(), creative_ads);

  transaction->commands.push_back(std::move(command));
}

void RedemptionValues::InsertOrUpdate(mojom::DBTransaction* transaction,
                                      const std::string& creative_instance_id,
                                      const double value) {
  DCHECK(transaction);
  DCHECK(!creative_instance_id.empty());

  mojom::DBCommandPtr command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::RUN;
  command->command =
      BuildInsertOrUpdateQuery(command.get(), creative_instance_id, value);

  transaction->commands.push_back(std::move(command));
}

void RedemptionValues::Delete(ResultCallback callback) {
  mojom::DBTransactionPtr transaction = mojom::DBTransaction::New();

  util::Delete(transaction.get(), GetTableName());

  AdsClientHelper::Get()->RunDBTransaction(
      std::move(transaction),
      std::bind(&OnResultCallback, std::placeholders::_1, callback));
}

void RedemptionValues::GetForCreativeInstanceId(
    const std::string& creative_instance_id,
    GetRedemptionValuesCallback callback) {
  if (creative_instance_id.empty()) {
    callback(/* success */ false, creative_instance_id, /* value */ 0.0);
    return;
  }

  const std::string& query = base::StringPrintf(
      "SELECT "
      "creative_instance_id, "
      "value "
      "FROM %s AS rv "
      "WHERE rv.creative_instance_id = '%s'",
      GetTableName().c_str(), creative_instance_id.c_str());

  mojom::DBCommandPtr command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::READ;
  command->command = query;

  command->record_bindings = {
      mojom::DBCommand::RecordBindingType::STRING_TYPE,  // creative_instance_id
      mojom::DBCommand::RecordBindingType::DOUBLE_TYPE   // value
  };

  mojom::DBTransactionPtr transaction = mojom::DBTransaction::New();
  transaction->commands.push_back(std::move(command));

  AdsClientHelper::Get()->RunDBTransaction(
      std::move(transaction),
      std::bind(&RedemptionValues::OnGetForCreativeInstanceId, this,
                std::placeholders::_1, creative_instance_id, callback));
}

std::string RedemptionValues::GetTableName() const {
  return kTableName;
}

void RedemptionValues::Migrate(mojom::DBTransaction* transaction,
                               const int to_version) {
  DCHECK(transaction);

  switch (to_version) {
    case 22: {
      MigrateToV22(transaction);
      break;
    }

    default: {
      break;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

std::string RedemptionValues::BuildInsertOrUpdateQuery(
    mojom::DBCommand* command,
    const CreativeAdList& creative_ads) {
  DCHECK(command);

  const int count = BindParameters(command, creative_ads);

  return base::StringPrintf(
      "INSERT OR REPLACE INTO %s "
      "(creative_instance_id, "
      "value) VALUES %s",
      GetTableName().c_str(),
      BuildBindingParameterPlaceholders(2, count).c_str());
}

std::string RedemptionValues::BuildInsertOrUpdateQuery(
    mojom::DBCommand* command,
    const std::string& creative_instance_id,
    const double value) {
  DCHECK(command);
  DCHECK(!creative_instance_id.empty());

  BindParameters(command, creative_instance_id, value);

  return base::StringPrintf(
      "INSERT OR REPLACE INTO %s "
      "(creative_instance_id, "
      "value) VALUES %s",
      GetTableName().c_str(), BuildBindingParameterPlaceholders(2, 1).c_str());
}

void RedemptionValues::OnGetForCreativeInstanceId(
    mojom::DBCommandResponsePtr response,
    const std::string& creative_instance_id,
    GetRedemptionValuesCallback callback) {
  if (!response ||
      response->status != mojom::DBCommandResponse::Status::RESPONSE_OK) {
    BLOG(0, "Failed to get redemption value");
    callback(/* success */ false, creative_instance_id, /* value */ 0.0);
    return;
  }

  mojom::DBRecordPtr record = response->result->get_records().front();
  const double value = ColumnDouble(record, 1);

  callback(/* success */ true, creative_instance_id, value);
}

void RedemptionValues::MigrateToV22(mojom::DBTransaction* transaction) {
  DCHECK(transaction);

  const std::string& query =
      "CREATE TABLE redemption_values "
      "(creative_instance_id TEXT NOT NULL, "
      "value DOUBLE NOT NULL, "
      "PRIMARY KEY (creative_instance_id), "
      "UNIQUE(creative_instance_id, value) ON CONFLICT REPLACE)";

  mojom::DBCommandPtr command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::EXECUTE;
  command->command = query;

  transaction->commands.push_back(std::move(command));
}

}  // namespace table
}  // namespace database
}  // namespace ads
