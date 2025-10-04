// Copyright (c) 2025 HRB Studios
#include "jackpotviewdialog.h"
#include "clientmodel.h"
#include "guiutil.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QVBoxLayout>

JackpotViewDialog::JackpotViewDialog(QWidget* parent) :
    QDialog(parent),
    clientModel(nullptr)
{
    setWindowTitle(tr("Jackpot Pools"));
    setMinimumWidth(300);

    miniJackpotLabel = new QLabel("Mini Jackpot: Loading...");
    minorJackpotLabel = new QLabel("Minor Jackpot: Loading...");
    majorJackpotLabel = new QLabel("Major Jackpot: Loading...");
    grandJackpotLabel = new QLabel("Grand Jackpot: Loading...");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(miniJackpotLabel);
    layout->addWidget(minorJackpotLabel);
    layout->addWidget(majorJackpotLabel);
    layout->addWidget(grandJackpotLabel);

    setLayout(layout);

    connect(&updateTimer, &QTimer::timeout, this, &JackpotViewDialog::updateJackpotValues);
    updateTimer.start(5000); // refresh every 5 seconds
}

void JackpotViewDialog::setClientModel(ClientModel* model)
{
    clientModel = model;
}

void JackpotViewDialog::updateJackpotValues()
{
    if (!clientModel) return;

    UniValue params(UniValue::VARR);
    UniValue result;

    try {
        result = clientModel->node().executeRpc("getjackpotpools", params);
    } catch (const UniValue& e) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to fetch jackpot values."));
        return;
    }

    if (result.isObject()) {
        QJsonDocument doc = QJsonDocument::fromVariant(result.get_obj());
        QJsonObject obj = doc.object();

        miniJackpotLabel->setText(tr("Mini Jackpot: %1 HRB").arg(obj["mini"].toString()));
        minorJackpotLabel->setText(tr("Minor Jackpot: %1 HRB").arg(obj["minor"].toString()));
        majorJackpotLabel->setText(tr("Major Jackpot: %1 HRB").arg(obj["major"].toString()));
        grandJackpotLabel->setText(tr("Grand Jackpot: %1 HRB").arg(obj["grand"].toString()));
    }
}
