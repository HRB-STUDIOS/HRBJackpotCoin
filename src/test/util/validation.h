// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_TEST_UTIL_VALIDATION_H
#define HRBJACKPOTCOIN_TEST_UTIL_VALIDATION_H

#include <validation.h>

class CValidationInterface;

struct TestChainstateManager : public ChainstateManager {
    /** Reset the ibd cache to its initial state */
    void ResetIbd();
    /** Toggle IsInitialBlockDownload from true to false */
    void JumpOutOfIbd();
};

class ValidationInterfaceTest
{
public:
    static void BlockConnected(
        ChainstateRole role,
        CValidationInterface& obj,
        const std::shared_ptr<const CBlock>& block,
        const CBlockIndex* pindex);
};

#endif // HRBJACKPOTCOIN_TEST_UTIL_VALIDATION_H
