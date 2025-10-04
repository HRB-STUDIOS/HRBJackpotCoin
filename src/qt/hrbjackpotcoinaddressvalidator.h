// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef hrbjackpotcoin_QT_hrbjackpotcoinADDRESSVALIDATOR_H
#define hrbjackpotcoin_QT_hrbjackpotcoinADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class HRBJackpotCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HRBJackpotCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** HRBJackpotCoin address widget validator, checks for a valid hrbjackpotcoin address.
 */
class HRBJackpotCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit HRBJackpotCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // hrbjackpotcoin_QT_hrbjackpotcoinADDRESSVALIDATOR_H
