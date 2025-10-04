// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_KERNEL_BLOCKMANAGER_OPTS_H
#define HRBJACKPOTCOIN_KERNEL_BLOCKMANAGER_OPTS_H

#include <kernel/notifications_interface.h>
#include <util/fs.h>

#include <cstdint>

class CChainParams;

namespace kernel {

/**
 * An options struct for `BlockManager`, more ergonomically referred to as
 * `BlockManager::Options` due to the using-declaration in `BlockManager`.
 */
struct BlockManagerOpts {
    const CChainParams& chainparams;
    uint64_t prune_target{0};
    bool fast_prune{false};
    const fs::path blocks_dir;
    Notifications& notifications;
};

} // namespace kernel

#endif // HRBJACKPOTCOIN_KERNEL_BLOCKMANAGER_OPTS_H
