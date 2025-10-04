// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_CRYPTO_HKDF_SHA256_32_H
#define HRBJACKPOTCOIN_CRYPTO_HKDF_SHA256_32_H

#include <crypto/hmac_sha256.h>

#include <cstdlib>
#include <stdint.h>

/** A rfc5869 HKDF implementation with HMAC_SHA256 and fixed key output length of 32 bytes (L=32) */
class CHKDF_HMAC_SHA256_L32
{
private:
    unsigned char m_prk[32];
    static const size_t OUTPUT_SIZE = 32;

public:
    CHKDF_HMAC_SHA256_L32(const unsigned char* ikm, size_t ikmlen, const std::string& salt);
    void Expand32(const std::string& info, unsigned char hash[OUTPUT_SIZE]);
};

#endif // HRBJACKPOTCOIN_CRYPTO_HKDF_SHA256_32_H
