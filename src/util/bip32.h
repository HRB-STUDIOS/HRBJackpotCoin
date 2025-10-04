// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_UTIL_BIP32_H
#define HRBJACKPOTCOIN_UTIL_BIP32_H

#include <cstdint>
#include <string>
#include <vector>

/** Parse an HD keypaths like "m/7/0'/2000". */
[[nodiscard]] bool ParseHDKeypath(const std::string& keypath_str, std::vector<uint32_t>& keypath);

/** Write HD keypaths as strings */
std::string WriteHDKeypath(const std::vector<uint32_t>& keypath, bool apostrophe = false);
std::string FormatHDKeypath(const std::vector<uint32_t>& path, bool apostrophe = false);

#endif // HRBJACKPOTCOIN_UTIL_BIP32_H
