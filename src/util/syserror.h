// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_UTIL_SYSERROR_H
#define HRBJACKPOTCOIN_UTIL_SYSERROR_H

#include <string>

/** Return system error string from errno value. Use this instead of
 * std::strerror, which is not thread-safe. For network errors use
 * NetworkErrorString from sock.h instead.
 */
std::string SysErrorString(int err);

#if defined(WIN32)
std::string Win32ErrorString(int err);
#endif

#endif // HRBJACKPOTCOIN_UTIL_SYSERROR_H
