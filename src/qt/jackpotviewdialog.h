// Copyright (c) 2025 HRB Studios
#ifndef HRBJACKPOTCOIN_QT_JACKPOTVIEWDIALOG_H
#define HRBJACKPOTCOIN_QT_JACKPOTVIEWDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>

class ClientModel;

class JackpotViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JackpotViewDialog(QWidget* parent = nullptr);
    void setClientModel(ClientModel* model);

private Q_SLOTS:
    void updateJackpotValues();

private:
    ClientModel* clientModel;
    QLabel* miniJackpotLabel;
    QLabel* minorJackpotLabel;
    QLabel* majorJackpotLabel;
    QLabel* grandJackpotLabel;
    QTimer updateTimer;
};

#endif // HRBJACKPOTCOIN_QT_JACKPOTVIEWDIALOG_H
