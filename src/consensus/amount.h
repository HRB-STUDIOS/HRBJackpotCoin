// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_CONSENSUS_AMOUNT_H
#define HRBJACKPOTCOIN_CONSENSUS_AMOUNT_H

#include <cstdint>

/** Amount in hrbjacks (Can be negative) */
typedef int64_t CAmount;

/** The amount of hrbjacks in one hrb. */
static constexpr CAmount COIN = 100000000;

/** No amount larger than this (in hrbjack) is valid.
 *
 * Note that this constant is *not* the total money supply, which in HRBJackpotCoin
 * currently happens to be less than 21,000,000 hrb for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static constexpr CAmount MAX_MONEY = 21000000 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

#endif // HRBJACKPOTCOIN_CONSENSUS_AMOUNT_H
