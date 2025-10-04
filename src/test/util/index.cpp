// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/util/index.h>

#include <index/base.h>
#include <shutdown.h>
#include <util/check.h>
#include <util/time.h>

void IndexWaitSynced(const BaseIndex& index)
{
    while (!index.BlockUntilSyncedToCurrentChain()) {
        // Assert shutdown was not requested to abort the test, instead of looping forever, in case
        // there was an unexpected error in the index that caused it to stop syncing and request a shutdown.
        Assert(!ShutdownRequested());

        UninterruptibleSleep(100ms);
    }
    assert(index.GetSummary().synced);
}
