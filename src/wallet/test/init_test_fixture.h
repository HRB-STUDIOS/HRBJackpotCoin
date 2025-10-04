// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_WALLET_TEST_INIT_TEST_FIXTURE_H
#define HRBJACKPOTCOIN_WALLET_TEST_INIT_TEST_FIXTURE_H

#include <interfaces/chain.h>
#include <interfaces/wallet.h>
#include <node/context.h>
#include <test/util/setup_common.h>
#include <util/chaintype.h>


namespace wallet {
struct InitWalletDirTestingSetup: public BasicTestingSetup {
    explicit InitWalletDirTestingSetup(const ChainType chain_type = ChainType::MAIN);
    ~InitWalletDirTestingSetup();
    void SetWalletDir(const fs::path& walletdir_path);

    fs::path m_datadir;
    fs::path m_cwd;
    std::map<std::string, fs::path> m_walletdir_path_cases;
    std::unique_ptr<interfaces::WalletLoader> m_wallet_loader;
};

#endif // HRBJACKPOTCOIN_WALLET_TEST_INIT_TEST_FIXTURE_H
} // namespace wallet
