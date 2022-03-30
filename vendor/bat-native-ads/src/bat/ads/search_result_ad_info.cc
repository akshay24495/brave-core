/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/search_result_ad_info.h"

#include "bat/ads/internal/json_helper.h"
#include "bat/ads/internal/logging.h"

namespace ads {

SearchResultAdInfo::SearchResultAdInfo() = default;

SearchResultAdInfo::SearchResultAdInfo(const SearchResultAdInfo& info) =
    default;

SearchResultAdInfo::~SearchResultAdInfo() = default;

bool SearchResultAdInfo::IsValid() const {
  if (!AdInfo::IsValid()) {
    return false;
  }

  if (headline_text.empty() || description.empty()) {
    return false;
  }

  return true;
}

std::string SearchResultAdInfo::ToJson() const {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

bool SearchResultAdInfo::FromJson(const std::string& json) {
  rapidjson::Document document;
  document.Parse(json.c_str());

  if (document.HasParseError()) {
    BLOG(1, helper::JSON::GetLastError(&document));
    return false;
  }

  if (document.HasMember("type")) {
    type = AdType(document["type"].GetString());
  }

  if (document.HasMember("uuid")) {
    uuid = document["uuid"].GetString();
  }

  if (document.HasMember("creative_instance_id")) {
    creative_instance_id = document["creative_instance_id"].GetString();
  }

  if (document.HasMember("creative_set_id")) {
    creative_set_id = document["creative_set_id"].GetString();
  }

  if (document.HasMember("campaign_id")) {
    campaign_id = document["campaign_id"].GetString();
  }

  if (document.HasMember("advertiser_id")) {
    advertiser_id = document["advertiser_id"].GetString();
  }

  if (document.HasMember("segment")) {
    segment = document["segment"].GetString();
  }

  if (document.HasMember("headline_text")) {
    headline_text = document["headline_text"].GetString();
  }

  if (document.HasMember("description")) {
    description = document["description"].GetString();
  }

  if (document.HasMember("target_url")) {
    target_url = document["target_url"].GetString();
  }

  return true;
}

void SaveToJson(JsonWriter* writer, const SearchResultAdInfo& info) {
  writer->StartObject();

  writer->String("type");
  writer->String(info.type.ToString().c_str());

  writer->String("uuid");
  writer->String(info.uuid.c_str());

  writer->String("creative_instance_id");
  writer->String(info.creative_instance_id.c_str());

  writer->String("creative_set_id");
  writer->String(info.creative_set_id.c_str());

  writer->String("campaign_id");
  writer->String(info.campaign_id.c_str());

  writer->String("advertiser_id");
  writer->String(info.advertiser_id.c_str());

  writer->String("segment");
  writer->String(info.segment.c_str());

  writer->String("headline_text");
  writer->String(info.headline_text.c_str());

  writer->String("description");
  writer->String(info.description.c_str());

  writer->String("target_url");
  writer->String(info.target_url.c_str());

  writer->EndObject();
}

}  // namespace ads
