// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <wallet/test/util.h>
#include <wallet/test/wallet_test_fixture.h>

#include <scheduler.h>
#include <util/chaintype.h>

namespace wallet {
WalletTestingSetup::WalletTestingSetup(const ChainType chainType)
    : TestingSetup(chainType),
      m_wallet_loader{interfaces::MakeWalletLoader(*m_node.chain, *Assert(m_node.args))},
      m_wallet(m_node.chain.get(), "", CreateMockableWalletDatabase())
{
    m_wallet.LoadWallet();
    m_chain_notifications_handler = m_node.chain->handleNotifications({ &m_wallet, [](CWallet*) {} });
    m_wallet_loader->registerRpcs();
}

WalletTestingSetup::~WalletTestingSetup()
{
    if (m_node.scheduler) m_node.scheduler->stop();
}
} // namespace wallet
