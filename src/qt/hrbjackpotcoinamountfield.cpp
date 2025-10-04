// Copyright (c) 2025 HRB Studios

// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.

// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
#include <qt/hrbjackpotcoinamountfield.h>

#include <qt/hrbjackpotcoinunits.h>
#include <qt/guiconstants.h>
#include <qt/guiutil.h>
#include <qt/qvaluecombobox.h>

#include <QApplication>
#include <QAbstractSpinBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QVariant>

#include <cassert>

/** QSpinBox that uses fixed-point numbers internally and uses our own
 * formatting/parsing functions.
 */
class AmountSpinBox: public QAbstractSpinBox
{
    Q_OBJECT

public:
    explicit AmountSpinBox(QWidget *parent):
        QAbstractSpinBox(parent)
    {
        setAlignment(Qt::AlignRight);

        connect(lineEdit(), &QLineEdit::textEdited, this, &AmountSpinBox::valueChanged);
    }

    QValidator::State validate(QString &text, int &pos) const override
    {
        if(text.isEmpty())
            return QValidator::Intermediate;
        bool valid = false;
        parse(text, &valid);
        /* Make sure we return Intermediate so that fixup() is called on defocus */
        return valid ? QValidator::Intermediate : QValidator::Invalid;
    }

    void fixup(QString &input) const override
    {
        bool valid;
        CAmount val;

        if (input.isEmpty() && !m_allow_empty) {
            valid = true;
            val = m_min_amount;
        } else {
            valid = false;
            val = parse(input, &valid);
        }

        if (valid) {
            val = qBound(m_min_amount, val, m_max_amount);
            input = HRBJackpotCoinUnits::format(currentUnit, val, false, HRBJackpotCoinUnits::SeparatorStyle::ALWAYS);
            lineEdit()->setText(input);
        }
    }

    CAmount value(bool *valid_out=nullptr) const
    {
        return parse(text(), valid_out);
    }

    void setValue(const CAmount& value)
    {
        lineEdit()->setText(HRBJackpotCoinUnits::format(currentUnit, value, false, HRBJackpotCoinUnits::SeparatorStyle::ALWAYS));
        Q_EMIT valueChanged();
    }

    void SetAllowEmpty(bool allow)
    {
        m_allow_empty = allow;
    }

    void SetMinValue(const CAmount& value)
    {
        m_min_amount = value;
    }

    void SetMaxValue(const CAmount& value)
    {
        m_max_amount = value;
    }

    void stepBy(int steps) override
    {
        bool valid = false;
        CAmount val = value(&valid);
        val = val + steps * singleStep;
        val = qBound(m_min_amount, val, m_max_amount);
        setValue(val);
    }

    void setDisplayUnit(HRBJackpotCoinUnit unit)
    {
        bool valid = false;
        CAmount val = value(&valid);

        currentUnit = unit;
        lineEdit()->setPlaceholderText(HRBJackpotCoinUnits::format(currentUnit, m_min_amount, false, HRBJackpotCoinUnits::SeparatorStyle::ALWAYS));
        if(valid)
            setValue(val);
        else
            clear();
    }

    void setSingleStep(const CAmount& step)
    {
        singleStep = step;
    }

    QSize minimumSizeHint() const override
    {
        if(cachedMinimumSizeHint.isEmpty())
        {
            ensurePolished();

            const QFontMetrics fm(fontMetrics());
            int h = lineEdit()->minimumSizeHint().height();
            int w = GUIUtil::TextWidth(fm, HRBJackpotCoinUnits::format(HRBJackpotCoinUnit::HRB, HRBJackpotCoinUnits::maxMoney(), false, HRBJackpotCoinUnits::SeparatorStyle::ALWAYS));
            w += 2; // cursor blinking space

            QStyleOptionSpinBox opt;
            initStyleOption(&opt);
            QSize hint(w, h);
            QSize extra(35, 6);
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
            // get closer to final result by repeating the calculation
            opt.rect.setSize(hint + extra);
            extra += hint - style()->subControlRect(QStyle::CC_SpinBox, &opt,
                                                    QStyle::SC_SpinBoxEditField, this).size();
            hint += extra;
            hint.setHeight(h);

            opt.rect = rect();

            cachedMinimumSizeHint = style()->sizeFromContents(QStyle::CT_SpinBox, &opt, hint, this);
        }
        return cachedMinimumSizeHint;
    }

private:
    HRBJackpotCoinUnit currentUnit{HRBJackpotCoinUnit::HRB};
    CAmount singleStep{CAmount(100000)}; // jackHRB
    mutable QSize cachedMinimumSizeHint;
    bool m_allow_empty{true};
    CAmount m_min_amount{CAmount(0)};
    CAmount m_max_amount{HRBJackpotCoinUnits::maxMoney()};

    /**
     * Parse a string into a number of base monetary units and
     * return validity.
     * @note Must return 0 if !valid.
     */
    CAmount parse(const QString &text, bool *valid_out=nullptr) const
    {
        CAmount val = 0;
        bool valid = HRBJackpotCoinUnits::parse(currentUnit, text, &val);
        if(valid)
        {
            if(val < 0 || val > HRBJackpotCoinUnits::maxMoney())
                valid = false;
        }
        if(valid_out)
            *valid_out = valid;
        return valid ? val : 0;
    }

protected:
    bool event(QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Comma)
            {
                // Translate a comma into a period
                QKeyEvent periodKeyEvent(event->type(), Qt::Key_Period, keyEvent->modifiers(), ".", keyEvent->isAutoRepeat(), keyEvent->count());
                return QAbstractSpinBox::event(&periodKeyEvent);
            }
        }
        return QAbstractSpinBox::event(event);
    }

    StepEnabled stepEnabled() const override
    {
        if (isReadOnly()) // Disable steps when AmountSpinBox is read-only
            return StepNone;
        if (text().isEmpty()) // Allow step-up with empty field
            return StepUpEnabled;

        StepEnabled rv = StepNone;
        bool valid = false;
        CAmount val = value(&valid);
        if (valid) {
            if (val > m_min_amount)
                rv |= StepDownEnabled;
            if (val < m_max_amount)
                rv |= StepUpEnabled;
        }
        return rv;
    }

Q_SIGNALS:
    void valueChanged();
};

#include <qt/hrbjackpotcoinamountfield.moc>

HRBJackpotCoinAmountField::HRBJackpotCoinAmountField(QWidget* parent)
    : QWidget(parent)
{
    amount = new AmountSpinBox(this);
    amount->setLocale(QLocale::c());
    amount->installEventFilter(this);
    amount->setMaximumWidth(240);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(amount);
    unit = new QValueComboBox(this);
    unit->setModel(new HRBJackpotCoinUnits(this));
    layout->addWidget(unit);
    layout->addStretch(1);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);

    setFocusPolicy(Qt::TabFocus);
    setFocusProxy(amount);

    // If one if the widgets changes, the combined content changes as well
    connect(amount, &AmountSpinBox::valueChanged, this, &HRBJackpotCoinAmountField::valueChanged);
    connect(unit, qOverload<int>(&QComboBox::currentIndexChanged), this, &HRBJackpotCoinAmountField::unitChanged);

    // Set default based on configuration
    unitChanged(unit->currentIndex());
}

void HRBJackpotCoinAmountField::clear()
{
    amount->clear();
    unit->setCurrentIndex(0);
}

void HRBJackpotCoinAmountField::setEnabled(bool fEnabled)
{
    amount->setEnabled(fEnabled);
    unit->setEnabled(fEnabled);
}

bool HRBJackpotCoinAmountField::validate()
{
    bool valid = false;
    value(&valid);
    setValid(valid);
    return valid;
}

void HRBJackpotCoinAmountField::setValid(bool valid)
{
    if (valid)
        amount->setStyleSheet("");
    else
        amount->setStyleSheet(STYLE_INVALID);
}

bool HRBJackpotCoinAmountField::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        // Clear invalid flag on focus
        setValid(true);
    }
    return QWidget::eventFilter(object, event);
}

QWidget *HRBJackpotCoinAmountField::setupTabChain(QWidget *prev)
{
    QWidget::setTabOrder(prev, amount);
    QWidget::setTabOrder(amount, unit);
    return unit;
}

CAmount HRBJackpotCoinAmountField::value(bool *valid_out) const
{
    return amount->value(valid_out);
}

void HRBJackpotCoinAmountField::setValue(const CAmount& value)
{
    amount->setValue(value);
}

void HRBJackpotCoinAmountField::SetAllowEmpty(bool allow)
{
    amount->SetAllowEmpty(allow);
}

void HRBJackpotCoinAmountField::SetMinValue(const CAmount& value)
{
    amount->SetMinValue(value);
}

void HRBJackpotCoinAmountField::SetMaxValue(const CAmount& value)
{
    amount->SetMaxValue(value);
}

void HRBJackpotCoinAmountField::setReadOnly(bool fReadOnly)
{
    amount->setReadOnly(fReadOnly);
}

void HRBJackpotCoinAmountField::unitChanged(int idx)
{
    // Use description tooltip for current unit for the combobox
    unit->setToolTip(unit->itemData(idx, Qt::ToolTipRole).toString());

    // Determine new unit ID
    QVariant new_unit = unit->currentData(HRBJackpotCoinUnits::UnitRole);
    assert(new_unit.isValid());
    amount->setDisplayUnit(new_unit.value<HRBJackpotCoinUnit>());
}

void HRBJackpotCoinAmountField::setDisplayUnit(HRBJackpotCoinUnit new_unit)
{
    unit->setValue(QVariant::fromValue(new_unit));
}

void HRBJackpotCoinAmountField::setSingleStep(const CAmount& step)
{
    amount->setSingleStep(step);
}
