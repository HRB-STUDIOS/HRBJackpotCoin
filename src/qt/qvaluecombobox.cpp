// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/qvaluecombobox.h>

QValueComboBox::QValueComboBox(QWidget* parent)
    : QComboBox(parent)
{
    connect(this, qOverload<int>(&QComboBox::currentIndexChanged), this, &QValueComboBox::handleSelectionChanged);
}

QVariant QValueComboBox::value() const
{
    return itemData(currentIndex(), role);
}

void QValueComboBox::setValue(const QVariant &value)
{
    setCurrentIndex(findData(value, role));
}

void QValueComboBox::setRole(int _role)
{
    this->role = _role;
}

void QValueComboBox::handleSelectionChanged(int idx)
{
    Q_EMIT valueChanged();
}
