/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/database/tables/redemption_values_database_table.h"

#include "bat/ads/internal/unittest_base.h"
#include "bat/ads/internal/unittest_util.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

class BatAdsRedemptionValuesDatabaseTableTest : public UnitTestBase {
 protected:
  BatAdsRedemptionValuesDatabaseTableTest() = default;
  ~BatAdsRedemptionValuesDatabaseTableTest() override = default;
};

TEST_F(BatAdsRedemptionValuesDatabaseTableTest, TableName) {
  // Arrange
  database::table::RedemptionValues database_table;

  // Act
  const std::string table_name = database_table.GetTableName();

  // Assert
  const std::string expected_table_name = "redemption_values";
  EXPECT_EQ(expected_table_name, table_name);
}

}  // namespace ads
