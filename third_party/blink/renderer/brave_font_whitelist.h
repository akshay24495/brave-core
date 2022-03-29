/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_THIRD_PARTY_BLINK_RENDERER_BRAVE_FONT_WHITELIST_H_
#define BRAVE_THIRD_PARTY_BLINK_RENDERER_BRAVE_FONT_WHITELIST_H_

#include <string>

#include "base/containers/flat_set.h"
#include "base/strings/string_piece.h"

namespace brave {

bool CanRestrictFontFamiliesOnThisPlatform();
const base::flat_set<base::StringPiece>& GetAllowedFontFamilies();

// This takes a 2-character language code.
const base::flat_set<base::StringPiece>&
GetAdditionalAllowedFontFamiliesByLocale(base::StringPiece locale_language);

}  // namespace brave

#endif  // BRAVE_THIRD_PARTY_BLINK_RENDERER_BRAVE_FONT_WHITELIST_H_
