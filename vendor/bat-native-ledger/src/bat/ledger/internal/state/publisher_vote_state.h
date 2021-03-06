/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_STATE_PUBLISHER_VOTE_STATE_H_
#define BRAVELEDGER_STATE_PUBLISHER_VOTE_STATE_H_

#include <string>
#include <vector>

#include "bat/ledger/internal/state/state_reader.h"
#include "bat/ledger/internal/state/state_writer.h"
#include "bat/ledger/internal/properties/publisher_vote_properties.h"
#include "rapidjson/writer.h"

namespace ledger {

using JsonWriter = rapidjson::Writer<rapidjson::StringBuffer>;

class PublisherVoteState
    : public state::Reader<PublisherVoteProperties>,
      public state::Writer<JsonWriter*, PublisherVoteProperties> {
 public:
  PublisherVoteState();
  ~PublisherVoteState();

  bool FromJson(
      const std::string& json,
      PublisherVoteProperties* properties) const override;

  bool FromDict(
      const base::DictionaryValue* dictionary,
      PublisherVoteProperties* properties) const override;

  bool ToJson(
      JsonWriter* writer,
      const PublisherVoteProperties& properties) const override;

  std::string ToJson(
      const PublisherVoteProperties& properties) const override;

  std::string ToJson(
      const BatchVotes& batch_votes) const;
};

}  // namespace ledger

#endif  // BRAVELEDGER_STATE_PUBLISHER_VOTE_STATE_H_
