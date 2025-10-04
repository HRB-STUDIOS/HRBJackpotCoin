// Copyright (c) 2025 HRB Studio's
// Copyright (c) 2025 The HRB Jackpot Coin  
// Distributed under the MIT software license, see the accompanying

#ifndef hrbjackpotcoin_SCRIPT_hrbjackpotcoinCONSENSUS_H
#define hrbjackpotcoin_SCRIPT_hrbjackpotcoinCONSENSUS_H

#include <stdint.h>

#if defined(BUILD_hrbjackpotcoin_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/hrbjackpotcoin-config.h>
  #if defined(_WIN32)
    #if defined(HAVE_DLLEXPORT_ATTRIBUTE)
      #define EXPORT_SYMBOL __declspec(dllexport)
    #else
      #define EXPORT_SYMBOL
    #endif
  #elif defined(HAVE_DEFAULT_VISIBILITY_ATTRIBUTE)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBhrbjackpotcoinCONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define hrbjackpotcoinCONSENSUS_API_VER 2

typedef enum hrbjackpotcoinconsensus_error_t
{
    hrbjackpotcoinconsensus_ERR_OK = 0,
    hrbjackpotcoinconsensus_ERR_TX_INDEX,
    hrbjackpotcoinconsensus_ERR_TX_SIZE_MISMATCH,
    hrbjackpotcoinconsensus_ERR_TX_DESERIALIZE,
    hrbjackpotcoinconsensus_ERR_AMOUNT_REQUIRED,
    hrbjackpotcoinconsensus_ERR_INVALID_FLAGS,
    hrbjackpotcoinconsensus_ERR_SPENT_OUTPUTS_REQUIRED,
    hrbjackpotcoinconsensus_ERR_SPENT_OUTPUTS_MISMATCH
} hrbjackpotcoinconsensus_error;

/** Script verification flags */
enum
{
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT             = (1U << 17), // enable TAPROOT (BIPs 341 & 342)
    hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_P2SH | hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_WITNESS |
                                                               hrbjackpotcoinconsensus_SCRIPT_FLAGS_VERIFY_TAPROOT
};

typedef struct {
    const unsigned char *scriptPubKey;
    unsigned int scriptPubKeySize;
    int64_t value;
} UTXO;

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int hrbjackpotcoinconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, hrbjackpotcoinconsensus_error* err);

EXPORT_SYMBOL int hrbjackpotcoinconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, hrbjackpotcoinconsensus_error* err);

EXPORT_SYMBOL int hrbjackpotcoinconsensus_verify_script_with_spent_outputs(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    const UTXO *spentOutputs, unsigned int spentOutputsLen,
                                    unsigned int nIn, unsigned int flags, hrbjackpotcoinconsensus_error* err);

EXPORT_SYMBOL unsigned int hrbjackpotcoinconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // hrbjackpotcoin_SCRIPT_hrbjackpotcoinCONSENSUS_H
