// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_UTIL_SERFLOAT_H
#define HRBJACKPOTCOIN_UTIL_SERFLOAT_H

#include <cstdint>

/* Encode a double using the IEEE 754 binary64 format. All NaNs are encoded as x86/ARM's
 * positive quiet NaN with payload 0. */
uint64_t EncodeDouble(double f) noexcept;
/* Reverse operation of DecodeDouble. DecodeDouble(EncodeDouble(f))==f unless isnan(f). */
double DecodeDouble(uint64_t v) noexcept;

#endif // HRBJACKPOTCOIN_UTIL_SERFLOAT_H
