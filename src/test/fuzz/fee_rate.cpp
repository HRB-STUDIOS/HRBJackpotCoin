// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <consensus/amount.h>
#include <policy/feerate.h>
#include <test/fuzz/FuzzedDataProvider.h>
#include <test/fuzz/fuzz.h>
#include <test/fuzz/util.h>

#include <cstdint>
#include <limits>
#include <string>
#include <vector>

FUZZ_TARGET(fee_rate)
{
    FuzzedDataProvider fuzzed_data_provider(buffer.data(), buffer.size());
    const CAmount hrbjacks_per_k = ConsumeMoney(fuzzed_data_provider);
    const CFeeRate fee_rate{hrbjacks_per_k};

    (void)fee_rate.GetFeePerK();
    const auto bytes = fuzzed_data_provider.ConsumeIntegral<uint32_t>();
    if (!MultiplicationOverflow(int64_t{bytes}, hrbjacks_per_k)) {
        (void)fee_rate.GetFee(bytes);
    }
    (void)fee_rate.ToString();

    const CAmount another_hrbjacks_per_k = ConsumeMoney(fuzzed_data_provider);
    CFeeRate larger_fee_rate{another_hrbjacks_per_k};
    larger_fee_rate += fee_rate;
    if (hrbjacks_per_k != 0 && another_hrbjacks_per_k != 0) {
        assert(fee_rate < larger_fee_rate);
        assert(!(fee_rate > larger_fee_rate));
        assert(!(fee_rate == larger_fee_rate));
        assert(fee_rate <= larger_fee_rate);
        assert(!(fee_rate >= larger_fee_rate));
        assert(fee_rate != larger_fee_rate);
    }
}
