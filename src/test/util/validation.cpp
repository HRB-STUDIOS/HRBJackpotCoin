// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test/util/validation.h>

#include <util/check.h>
#include <util/time.h>
#include <validation.h>
#include <validationinterface.h>

void TestChainstateManager::ResetIbd()
{
    m_cached_finished_ibd = false;
    assert(IsInitialBlockDownload());
}

void TestChainstateManager::JumpOutOfIbd()
{
    Assert(IsInitialBlockDownload());
    m_cached_finished_ibd = true;
    Assert(!IsInitialBlockDownload());
}

void ValidationInterfaceTest::BlockConnected(
        ChainstateRole role,
        CValidationInterface& obj,
        const std::shared_ptr<const CBlock>& block,
        const CBlockIndex* pindex)
{
    obj.BlockConnected(role, block, pindex);
}
