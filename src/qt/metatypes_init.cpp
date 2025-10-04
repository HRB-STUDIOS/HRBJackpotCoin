// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.

#include <interfaces/node.h>            // interfaces::BlockAndHeaderTipInfo
#include <qt/hrbjackpotcoinunits.h>     // HRBJackpotCoinUnits::Unit
#include <QMetaType>
#include <QCoreApplication>

namespace {
void RegisterAll()
{
    // Fixes: "Cannot queue arguments of type 'interfaces::BlockAndHeaderTipInfo'"
    qRegisterMetaType<interfaces::BlockAndHeaderTipInfo>("interfaces::BlockAndHeaderTipInfo");

    // Mutes QVariant load complaints for the unit type (saving may still warn, but won’t freeze)
    qRegisterMetaType<HRBJackpotCoinUnits::Unit>("HRBJackpotCoinUnits::Unit");
}
} // namespace

Q_COREAPP_STARTUP_FUNCTION(RegisterAll)
CPP
