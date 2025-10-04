// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H
#define HRBJACKPOTCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H

#include <wallet/scriptpubkeyman.h>

#include <memory>

namespace wallet {
class ExternalSignerScriptPubKeyMan : public DescriptorScriptPubKeyMan
{
  public:
  ExternalSignerScriptPubKeyMan(WalletStorage& storage, WalletDescriptor& descriptor, int64_t keypool_size)
      :   DescriptorScriptPubKeyMan(storage, descriptor, keypool_size)
      {}
  ExternalSignerScriptPubKeyMan(WalletStorage& storage, int64_t keypool_size)
      :   DescriptorScriptPubKeyMan(storage, keypool_size)
      {}

  /** Provide a descriptor at setup time
  * Returns false if already setup or setup fails, true if setup is successful
  */
  bool SetupDescriptor(std::unique_ptr<Descriptor>desc);

  static ExternalSigner GetExternalSigner();

  bool DisplayAddress(const CScript scriptPubKey, const ExternalSigner &signer) const;

  TransactionError FillPSBT(PartiallySignedTransaction& psbt, const PrecomputedTransactionData& txdata, int sighash_type = 1 /* SIGHASH_ALL */, bool sign = true, bool bip32derivs = false, int* n_signed = nullptr, bool finalize = true) const override;
};
} // namespace wallet
#endif // HRBJACKPOTCOIN_WALLET_EXTERNAL_SIGNER_SCRIPTPUBKEYMAN_H
