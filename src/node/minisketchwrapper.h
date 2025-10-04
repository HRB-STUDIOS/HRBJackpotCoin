// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_NODE_MINISKETCHWRAPPER_H
#define HRBJACKPOTCOIN_NODE_MINISKETCHWRAPPER_H

#include <minisketch.h>

#include <cstddef>
#include <cstdint>

namespace node {
/** Wrapper around Minisketch::Minisketch(32, implementation, capacity). */
Minisketch MakeMinisketch32(size_t capacity);
/** Wrapper around Minisketch::CreateFP. */
Minisketch MakeMinisketch32FP(size_t max_elements, uint32_t fpbits);
} // namespace node

#endif // HRBJACKPOTCOIN_NODE_MINISKETCHWRAPPER_H
