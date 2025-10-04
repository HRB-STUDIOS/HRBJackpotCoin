// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_ATTRIBUTES_H
#define HRBJACKPOTCOIN_ATTRIBUTES_H

#if defined(__clang__)
#  if __has_attribute(lifetimebound)
#    define LIFETIMEBOUND [[clang::lifetimebound]]
#  else
#    define LIFETIMEBOUND
#  endif
#else
#  define LIFETIMEBOUND
#endif

#if defined(__GNUC__)
#  define ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#  define ALWAYS_INLINE __forceinline
#else
#  error No known always_inline attribute for this platform.
#endif

#endif // HRBJACKPOTCOIN_ATTRIBUTES_H
