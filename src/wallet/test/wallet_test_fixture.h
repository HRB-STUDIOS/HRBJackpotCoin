// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_WALLET_TEST_WALLET_TEST_FIXTURE_H
#define HRBJACKPOTCOIN_WALLET_TEST_WALLET_TEST_FIXTURE_H

#include <test/util/setup_common.h>

#include <interfaces/chain.h>
#include <interfaces/wallet.h>
#include <node/context.h>
#include <util/chaintype.h>
#include <util/check.h>
#include <wallet/wallet.h>

#include <memory>

namespace wallet {
/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup : public TestingSetup {
    explicit WalletTestingSetup(const ChainType chainType = ChainType::MAIN);
    ~WalletTestingSetup();

    std::unique_ptr<interfaces::WalletLoader> m_wallet_loader;
    CWallet m_wallet;
    std::unique_ptr<interfaces::Handler> m_chain_notifications_handler;
};
} // namespace wallet

#endif // HRBJACKPOTCOIN_WALLET_TEST_WALLET_TEST_FIXTURE_H
