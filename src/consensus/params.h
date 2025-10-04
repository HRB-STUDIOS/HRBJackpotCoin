// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license.

#ifndef HRBJACKPOTCOIN_CONSENSUS_PARAMS_H
#define HRBJACKPOTCOIN_CONSENSUS_PARAMS_H

#if __has_include("amount.h")
#include "amount.h"
#elif __has_include("../amount.h")
#include "../amount.h"
#else
#error "Cannot locate amount.h"
#endif
#include <uint256.h>
#include <chrono>
#include <limits>
#include <map>
#include <vector>
#include <string>

// HRB Jackpot Coin: Include for CScript - needed for wallet addresses
#include <script/script.h>

namespace Consensus {

enum BuriedDeployment : int16_t {
    DEPLOYMENT_HEIGHTINCB = std::numeric_limits<int16_t>::min(),
    DEPLOYMENT_CLTV,
    DEPLOYMENT_DERSIG,
    DEPLOYMENT_CSV,
    DEPLOYMENT_SEGWIT,
};
constexpr bool ValidDeployment(BuriedDeployment dep) { return dep <= DEPLOYMENT_SEGWIT; }

enum DeploymentPos : uint16_t {
    DEPLOYMENT_TESTDUMMY,
    DEPLOYMENT_TAPROOT,
    MAX_VERSION_BITS_DEPLOYMENTS
};
constexpr bool ValidDeployment(DeploymentPos dep) { return dep < MAX_VERSION_BITS_DEPLOYMENTS; }

struct BIP9Deployment {
    int bit{28};
    int64_t nStartTime{NEVER_ACTIVE};
    int64_t nTimeout{NEVER_ACTIVE};
    int min_activation_height{0};

    static constexpr int64_t NO_TIMEOUT = std::numeric_limits<int64_t>::max();
    static constexpr int64_t ALWAYS_ACTIVE = -1;
    static constexpr int64_t NEVER_ACTIVE = -2;
};

struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;

    std::map<uint256, uint32_t> script_flag_exceptions;
    int BIP34Height;
    uint256 BIP34Hash;
    int BIP65Height;
    int BIP66Height;
    int CSVHeight;
    int SegwitHeight;
    int MinBIP9WarningHeight;

    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];

    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    std::chrono::seconds PowTargetSpacing() const {
        return std::chrono::seconds{nPowTargetSpacing};
    }
    int64_t DifficultyAdjustmentInterval() const {
        return nPowTargetTimespan / nPowTargetSpacing;
    }

    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;

    bool signet_blocks{false};
    std::vector<uint8_t> signet_challenge;

    // ✅ HRB Jackpot Coin: Tokenomics
    int nInitialBlockRewardHRB;
    int nBlockTimeDoublingInterval;

    // ✅ Jackpot reward seed values (reset value after a win)
    CAmount nJackpotMiniSeed;
    CAmount nJackpotMinorSeed;
    CAmount nJackpotMajorSeed;
    CAmount nJackpotGrandSeed;

    // ✅ Jackpot odds (inverse: 1 in N chance)
    int jackpotMiniOdds;
    int jackpotMinorOdds;
    int jackpotMajorOdds;
    int jackpotGrandOdds;

    // ✅ Repayment logic for seed reimbursement
    std::string sJackpotOwnerRepaymentAddress;
    int nJackpotOwnerRepaymentPercentage; // percentage repaid to seed funder before jackpots grow freely

    // ✅ Anti-cheat threshold (hashrate limits, device detection)
    int nAntiCheatHashrateThreshold;
    int nAntiCheatMaxSoftFlags;

    // HRB Jackpot Coin: CScript destinations for jackpot distribution
    CScript founder_reimbursement_script;
    CScript mini_jackpot_script;
    CScript minor_jackpot_script;
    CScript major_jackpot_script;
    CScript grand_jackpot_script;
    CScript coinbase_miner_script_pubkey;

    // ✅ Jackpot destination address strings for dynamic assignment (used in chainparams)
    std::string jackpot_founder_address;
    std::string jackpot_mini_address;
    std::string jackpot_minor_address;
    std::string jackpot_major_address;
    std::string jackpot_grand_address;

    // ✅ Toggle to control jackpot activation
    bool jackpots_enabled = false;
    int DeploymentHeight(BuriedDeployment dep) const {
        switch (dep) {
            case DEPLOYMENT_HEIGHTINCB: return BIP34Height;
            case DEPLOYMENT_CLTV: return BIP65Height;
            case DEPLOYMENT_DERSIG: return BIP66Height;
            case DEPLOYMENT_CSV: return CSVHeight;
            case DEPLOYMENT_SEGWIT: return SegwitHeight;
        }
        return std::numeric_limits<int>::max();
    }
};

} // namespace Consensus

#endif // HRBJACKPOTCOIN_CONSENSUS_PARAMS_H