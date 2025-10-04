// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/transactionoverviewwidget.h>

#include <qt/transactiontablemodel.h>

#include <QListView>
#include <QSize>
#include <QSizePolicy>

TransactionOverviewWidget::TransactionOverviewWidget(QWidget* parent)
    : QListView(parent) {}

QSize TransactionOverviewWidget::sizeHint() const
{
    return {sizeHintForColumn(TransactionTableModel::ToAddress), QListView::sizeHint().height()};
}

void TransactionOverviewWidget::showEvent(QShowEvent* event)
{
    Q_UNUSED(event);
    QSizePolicy sp = sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    setSizePolicy(sp);
}
