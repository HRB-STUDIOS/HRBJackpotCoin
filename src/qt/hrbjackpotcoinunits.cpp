// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <qt/hrbjackpotcoinunits.h>
#include <qt/optionsmodel.h>

#include <QSettings>
#include <QLocale>
#include <QStringList>
#include <cmath>

static QString thinSpace()
{
    return QString::fromUtf8(THIN_SP_UTF8);
}

HRBJackpotCoinUnits::HRBJackpotCoinUnits(QObject* parent)
    : QAbstractListModel(parent)
{
    unitlist = availableUnits();
}

// --- Static helpers for this translation unit --------------------------------

static bool UnitValid(HRBJackpotCoinUnits::Unit u)
{
    switch (u) {
    case HRBJackpotCoinUnits::Unit::HRB:
    case HRBJackpotCoinUnits::Unit::mhrb:
    case HRBJackpotCoinUnits::Unit::uhrb:
    case HRBJackpotCoinUnits::Unit::jackHRB:
        return true;
    }
    return false;
}

// --- Public static API -------------------------------------------------------

QList<HRBJackpotCoinUnits::Unit> HRBJackpotCoinUnits::availableUnits()
{
    return { Unit::HRB, Unit::mhrb, Unit::uhrb, Unit::jackHRB };
}

QString HRBJackpotCoinUnits::longName(Unit unit)
{
    switch (unit) {
    case Unit::HRB:     return QStringLiteral("HRB");
    case Unit::mhrb:    return QStringLiteral("mHRB");
    case Unit::uhrb:    return QStringLiteral("μHRB");
    case Unit::jackHRB: return QStringLiteral("jack");
    }
    // Fallback to avoid crashes if something unexpected slips through
    return QStringLiteral("HRB");
}

QString HRBJackpotCoinUnits::shortName(Unit unit)
{
    // Same as long names for now
    switch (unit) {
    case Unit::HRB:     return QStringLiteral("HRB");
    case Unit::mhrb:    return QStringLiteral("mHRB");
    case Unit::uhrb:    return QStringLiteral("μHRB");
    case Unit::jackHRB: return QStringLiteral("jack");
    }
    return QStringLiteral("HRB");
}

QString HRBJackpotCoinUnits::description(Unit unit)
{
    switch (unit) {
    case Unit::HRB:     return QStringLiteral("HRB");
    case Unit::mhrb:    return QStringLiteral("Milli-HRB (1 / 1 000)");
    case Unit::uhrb:    return QStringLiteral("Micro-HRB (1 / 1 000 000)");
    case Unit::jackHRB: return QStringLiteral("jack (1 / 100 000 000 HRB)");
    }
    return QStringLiteral("HRB");
}

qint64 HRBJackpotCoinUnits::factor(Unit unit)
{
    switch (unit) {
    case Unit::HRB:     return 100000000; // 1 HRB  = 100,000,000 jack
    case Unit::mhrb:    return 100000;    // 1 mHRB = 100,000 jack
    case Unit::uhrb:    return 100;       // 1 μHRB = 100 jack
    case Unit::jackHRB: return 1;         // 1 jack
    }
    return 100000000;
}

int HRBJackpotCoinUnits::decimals(Unit unit)
{
    switch (unit) {
    case Unit::HRB:     return 8;
    case Unit::mhrb:    return 5;
    case Unit::uhrb:    return 2;
    case Unit::jackHRB: return 0;
    }
    return 8;
}

static QString formatIntegerWithSeps(const QString& s, HRBJackpotCoinUnits::SeparatorStyle seps)
{
    if (seps == HRBJackpotCoinUnits::SeparatorStyle::NEVER) return s;
    QString out = s;
    int i = out.size();
    int counter = 0;
    while (i > 1) {
        ++counter;
        --i;
        if (counter % 3 == 0) {
            out.insert(i, thinSpace());
        }
    }
    return out;
}

QString HRBJackpotCoinUnits::format(Unit unit, const CAmount& amount, bool plussign,
                                    SeparatorStyle separators, bool justify)
{
    if (!UnitValid(unit)) unit = Unit::HRB;

    const qint64 coin = factor(unit);
    const int num_decimals = decimals(unit);

    const qint64 n_abs = (amount >= 0) ? amount : -amount;
    const qint64 quotient = n_abs / coin;
    const qint64 remainder = n_abs % coin;

    QString quotient_str = QString::number(quotient);
    if (justify) {
        int target = 16; // generous width
        if (quotient_str.size() < target)
            quotient_str = QString(target - quotient_str.size(), QLatin1Char(' ')) + quotient_str;
    }
    quotient_str = formatIntegerWithSeps(quotient_str, separators);

    QString sign;
    if (amount < 0) sign = QStringLiteral("-");
    else if (plussign && amount > 0) sign = QStringLiteral("+");

    if (num_decimals == 0) {
        return sign + quotient_str;
    }

    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, QLatin1Char('0'));

    // Trim trailing zeros (keep at least 2 decimals for HRB)
    int trim_floor = (unit == Unit::HRB) ? 2 : 0;
    int trim = 0;
    for (int i = remainder_str.size() - 1; i >= trim_floor; --i) {
        if (remainder_str.at(i) == QLatin1Char('0')) ++trim;
        else break;
    }
    if (trim > 0) remainder_str.chop(trim);

    QString out = sign + quotient_str;
    if (!remainder_str.isEmpty()) {
        out += QStringLiteral(".");
        out += remainder_str;
    }
    return out;
}

QString HRBJackpotCoinUnits::formatWithUnit(Unit unit, const CAmount& amount, bool plussign,
                                            SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QStringLiteral(" ") + shortName(unit);
}

QString HRBJackpotCoinUnits::formatHtmlWithUnit(Unit unit, const CAmount& amount, bool plussign,
                                                SeparatorStyle separators)
{
    QString out = formatWithUnit(unit, amount, plussign, separators);
    out.replace(THIN_SP_UTF8, THIN_SP_HTML);
    return QStringLiteral("<span style='white-space: nowrap;'>%1</span>").arg(out);
}

QString HRBJackpotCoinUnits::formatWithPrivacy(Unit unit, const CAmount& amount,
                                               SeparatorStyle separators, bool privacy)
{
    // If privacy mode, show a fixed-width obfuscated amount
    if (privacy) {
        QString value = QStringLiteral("########");
        if (decimals(unit) > 0) value += QStringLiteral(".####");
        return value + QStringLiteral(" ") + shortName(unit);
    }
    return formatWithUnit(unit, amount, false, separators);
}

bool HRBJackpotCoinUnits::parse(Unit unit, const QString& value, CAmount* val_out)
{
    if (!UnitValid(unit) || value.isEmpty()) return false;

    QString input = removeSpaces(value);
    int num_decimals = decimals(unit);

    // Split into whole and decimals
    const int dot = input.indexOf(QLatin1Char('.'));
    QString whole = input, decimals_part;
    if (dot > -1) {
        whole = input.left(dot);
        decimals_part = input.mid(dot + 1);
    }
    if (decimals_part.size() > num_decimals) return false;

    // Compose a plain integer string of jack units
    QString str = whole + decimals_part.leftJustified(num_decimals, QLatin1Char('0'));

    if (str.size() > 18) return false; // too big (avoid overflow)

    bool ok = false;
    qint64 n = str.toLongLong(&ok);
    if (!ok) return false;

    if (val_out) *val_out = n;
    return true;
}

QString HRBJackpotCoinUnits::getAmountColumnTitle(Unit unit)
{
    return QObject::tr("Amount") + QStringLiteral(" (") + shortName(unit) + QStringLiteral(")");
}

int HRBJackpotCoinUnits::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant HRBJackpotCoinUnits::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= unitlist.size())
        return QVariant();

    const Unit unit = unitlist.at(index.row());
    switch (role) {
    case Qt::DisplayRole:  return longName(unit);
    case Qt::ToolTipRole:  return description(unit);
    case UnitRole:         return QVariant::fromValue(unit);
    }
    return QVariant();
}

CAmount HRBJackpotCoinUnits::maxMoney()
{
    // Adjust to your network’s MAX_MONEY if defined elsewhere.
    // 21 million HRB by default, like Bitcoin. Change if needed.
    return 21'000'000LL * factor(Unit::HRB);
}

// --- QDataStream for enum ----------------------------------------------------

QDataStream& operator<<(QDataStream& out, const HRBJackpotCoinUnit& unit)
{
    out << static_cast<qint32>(unit);
    return out;
}

QDataStream& operator>>(QDataStream& in, HRBJackpotCoinUnit& unit)
{
    qint32 v;
    in >> v;
    auto u = static_cast<HRBJackpotCoinUnits::Unit>(v);
    if (!UnitValid(u)) u = HRBJackpotCoinUnits::Unit::HRB;
    unit = u;
    return in;
}
