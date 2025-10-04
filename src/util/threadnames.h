// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_UTIL_THREADNAMES_H
#define HRBJACKPOTCOIN_UTIL_THREADNAMES_H

#include <string>

namespace util {
//! Rename a thread both in terms of an internal (in-memory) name as well
//! as its system thread name.
//! @note Do not call this for the main thread, as this will interfere with
//! UNIX utilities such as top and killall. Use ThreadSetInternalName instead.
void ThreadRename(std::string&&);

//! Set the internal (in-memory) name of the current thread only.
void ThreadSetInternalName(std::string&&);

//! Get the thread's internal (in-memory) name; used e.g. for identification in
//! logging.
const std::string& ThreadGetInternalName();

} // namespace util

#endif // HRBJACKPOTCOIN_UTIL_THREADNAMES_H
