// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>
#include <consensus/consensus.h>
#include <core_io.h>
#include <policy/policy.h>
#include <script/script.h>
#include <test/fuzz/FuzzedDataProvider.h>
#include <test/fuzz/fuzz.h>
#include <test/fuzz/util.h>
#include <univalue.h>
#include <util/chaintype.h>

void initialize_script_format()
{
    SelectParams(ChainType::REGTEST);
}

FUZZ_TARGET(script_format, .init = initialize_script_format)
{
    FuzzedDataProvider fuzzed_data_provider(buffer.data(), buffer.size());
    const CScript script{ConsumeScript(fuzzed_data_provider)};
    if (script.size() > MAX_STANDARD_TX_WEIGHT / WITNESS_SCALE_FACTOR) {
        return;
    }

    (void)FormatScript(script);
    (void)ScriptToAsmStr(script, /*fAttemptSighashDecode=*/fuzzed_data_provider.ConsumeBool());

    UniValue o1(UniValue::VOBJ);
    ScriptToUniv(script, /*out=*/o1, /*include_hex=*/fuzzed_data_provider.ConsumeBool(), /*include_address=*/fuzzed_data_provider.ConsumeBool());
}
