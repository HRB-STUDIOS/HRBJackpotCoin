// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <rpc/client.h>
#include <rpc/util.h>
#include <test/fuzz/fuzz.h>
#include <util/chaintype.h>

#include <limits>
#include <string>

void initialize_parse_univalue()
{
    SelectParams(ChainType::REGTEST);
}

FUZZ_TARGET(parse_univalue, .init = initialize_parse_univalue)
{
    const std::string random_string(buffer.begin(), buffer.end());
    bool valid = true;
    const UniValue univalue = [&] {
        UniValue uv;
        if (!uv.read(random_string)) valid = false;
        return valid ? uv : UniValue{};
    }();
    if (!valid) {
        return;
    }
    try {
        (void)ParseHashO(univalue, "A");
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseHashO(univalue, random_string);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseHashV(univalue, "A");
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseHashV(univalue, random_string);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseHexO(univalue, "A");
    } catch (const UniValue&) {
    }
    try {
        (void)ParseHexO(univalue, random_string);
    } catch (const UniValue&) {
    }
    try {
        (void)ParseHexV(univalue, "A");
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseHexV(univalue, random_string);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        if (univalue.isNull() || univalue.isStr()) (void)ParseSighashString(univalue);
    } catch (const UniValue&) {
    }
    try {
        (void)AmountFromValue(univalue);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        FlatSigningProvider provider;
        (void)EvalDescriptorStringOrObject(univalue, provider);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseConfirmTarget(univalue, std::numeric_limits<unsigned int>::max());
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
    try {
        (void)ParseDescriptorRange(univalue);
    } catch (const UniValue&) {
    } catch (const std::runtime_error&) {
    }
}
