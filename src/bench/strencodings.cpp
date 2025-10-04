// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <bench/bench.h>
#include <bench/data.h>
#include <util/strencodings.h>

static void HexStrBench(benchmark::Bench& bench)
{
    auto const& data = benchmark::data::block413567;
    bench.batch(data.size()).unit("byte").run([&] {
        auto hex = HexStr(data);
        ankerl::nanobench::doNotOptimizeAway(hex);
    });
}

BENCHMARK(HexStrBench, benchmark::PriorityLevel::HIGH);
