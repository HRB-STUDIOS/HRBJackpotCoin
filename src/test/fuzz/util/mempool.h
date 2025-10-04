// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_TEST_FUZZ_UTIL_MEMPOOL_H
#define HRBJACKPOTCOIN_TEST_FUZZ_UTIL_MEMPOOL_H

#include <kernel/mempool_entry.h>
#include <validation.h>

class CTransaction;
class CTxMemPool;
class FuzzedDataProvider;

class DummyChainState final : public Chainstate
{
public:
    void SetMempool(CTxMemPool* mempool)
    {
        m_mempool = mempool;
    }
};

[[nodiscard]] CTxMemPoolEntry ConsumeTxMemPoolEntry(FuzzedDataProvider& fuzzed_data_provider, const CTransaction& tx) noexcept;

#endif // HRBJACKPOTCOIN_TEST_FUZZ_UTIL_MEMPOOL_H
