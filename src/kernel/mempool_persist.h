// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_KERNEL_MEMPOOL_PERSIST_H
#define HRBJACKPOTCOIN_KERNEL_MEMPOOL_PERSIST_H

#include <util/fs.h>

class Chainstate;
class CTxMemPool;

namespace kernel {

/** Dump the mempool to a file. */
bool DumpMempool(const CTxMemPool& pool, const fs::path& dump_path,
                 fsbridge::FopenFn mockable_fopen_function = fsbridge::fopen,
                 bool skip_file_commit = false);

struct ImportMempoolOptions {
    fsbridge::FopenFn mockable_fopen_function{fsbridge::fopen};
    bool use_current_time{false};
    bool apply_fee_delta_priority{true};
    bool apply_unbroadcast_set{true};
};
/** Import the file and attempt to add its contents to the mempool. */
bool LoadMempool(CTxMemPool& pool, const fs::path& load_path,
                 Chainstate& active_chainstate,
                 ImportMempoolOptions&& opts);

} // namespace kernel


#endif // HRBJACKPOTCOIN_KERNEL_MEMPOOL_PERSIST_H
