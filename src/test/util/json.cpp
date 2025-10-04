// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/util/json.h>

#include <string>
#include <util/check.h>

#include <univalue.h>

UniValue read_json(const std::string& jsondata)
{
    UniValue v;
    Assert(v.read(jsondata) && v.isArray());
    return v.get_array();
}
