// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_POLICY_FEERATE_H
#define HRBJACKPOTCOIN_POLICY_FEERATE_H

#include <consensus/amount.h>
#include <serialize.h>


#include <cstdint>
#include <string>
#include <type_traits>

const std::string CURRENCY_UNIT = "hrb"; // One formatted unit
const std::string CURRENCY_ATOM = "sat"; // One indivisible minimum value unit

/* Used to determine type of fee estimation requested */
enum class FeeEstimateMode {
    UNSET,        //!< Use default settings based on other criteria
    ECONOMICAL,   //!< Force estimateSmartFee to use non-conservative estimates
    CONSERVATIVE, //!< Force estimateSmartFee to use conservative estimates
    hrb_KVB,      //!< Use hrb/kvB fee rate unit
    SAT_VB,       //!< Use sat/vB fee rate unit
};

/**
 * Fee rate in hrbjacks per kilovirtualbyte: CAmount / kvB
 */
class CFeeRate
{
private:
    /** Fee rate in sat/kvB (hrbjacks per 1000 virtualbytes) */
    CAmount nHRBJacksPerK;

public:
    /** Fee rate of 0 hrbjacks per kvB */
    CFeeRate() : nHRBJacksPerK(0) { }
    template<typename I>
    explicit CFeeRate(const I _nHRBJacksPerK): nHRBJacksPerK(_nHRBJacksPerK) {
        // We've previously had bugs creep in from silent double->int conversion...
        static_assert(std::is_integral<I>::value, "CFeeRate should be used without floats");
    }

    /**
     * Construct a fee rate from a fee in hrbjacks and a vsize in vB.
     *
     * param@[in]   nFeePaid    The fee paid by a transaction, in hrbjacks
     * param@[in]   num_bytes   The vsize of a transaction, in vbytes
     */
    CFeeRate(const CAmount& nFeePaid, uint32_t num_bytes);

    /**
     * Return the fee in hrbjacks for the given vsize in vbytes.
     * If the calculated fee would have fractional hrbjacks, then the
     * returned fee will always be rounded up to the nearest hrbjack.
     */
    CAmount GetFee(uint32_t num_bytes) const;

    /**
     * Return the fee in hrbjacks for a vsize of 1000 vbytes
     */
    CAmount GetFeePerK() const { return nHRBJacksPerK; }
    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK < b.nHRBJacksPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK > b.nHRBJacksPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK == b.nHRBJacksPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK <= b.nHRBJacksPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK >= b.nHRBJacksPerK; }
    friend bool operator!=(const CFeeRate& a, const CFeeRate& b) { return a.nHRBJacksPerK != b.nHRBJacksPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nHRBJacksPerK += a.nHRBJacksPerK; return *this; }
    std::string ToString(const FeeEstimateMode& fee_estimate_mode = FeeEstimateMode::hrb_KVB) const;

    SERIALIZE_METHODS(CFeeRate, obj) { READWRITE(obj.nHRBJacksPerK); }
};

#endif // HRBJACKPOTCOIN_POLICY_FEERATE_H
