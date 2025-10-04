// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT

#ifndef HRBJACKPOTCOIN_QT_HRBJACKPOTCOIN_H
#define HRBJACKPOTCOIN_QT_HRBJACKPOTCOIN_H

#if defined(HAVE_CONFIG_H)
#include <config/hrbjackpotcoin-config.h>
#endif

#include <interfaces/node.h>
#include <qt/initexecutor.h>

#include <assert.h>
#include <memory>
#include <optional>
#include <cstdint>

#include <QApplication>

class HRBJackpotCoinGUI;
class ClientModel;
class NetworkStyle;
class OptionsModel;
class PaymentServer;
class PlatformStyle;
class SplashScreen;
class WalletController;
class WalletModel;
class QTimer;

namespace interfaces {
class Init;
} // namespace interfaces

/** Main HRBJackpotCoin application object */
class HRBJackpotCoinApplication : public QApplication
{
    Q_OBJECT
public:
    explicit HRBJackpotCoinApplication();
    ~HRBJackpotCoinApplication();

#ifdef ENABLE_WALLET
    /// Create payment server
    void createPaymentServer();
#endif
    /// parameter interaction/setup based on rules
    void parameterSetup();
    /// Create options model
    [[nodiscard]] bool createOptionsModel(bool resetSettings);
    /// Initialize prune setting
    void InitPruneSetting(std::int64_t prune_MiB);
    /// Create main window
    void createWindow(const NetworkStyle* networkStyle);
    /// Create splash screen
    void createSplashScreen(const NetworkStyle* networkStyle);
    /// Create or spawn node
    void createNode(interfaces::Init& init);
    /// Basic initialization, before starting initialization/shutdown thread. Return true on success.
    bool baseInitialize();

    /// Request core initialization
    void requestInitialize();

    /// Get window identifier of QMainWindow (HRBJackpotCoinGUI)
    WId getMainWinId() const;

    /// Setup platform style
    void setupPlatformStyle();

    interfaces::Node& node() const { assert(m_node); return *m_node; }

public Q_SLOTS:
#ifdef ENABLE_WALLET
    void quickSetupWallets();
#endif
    void initializeResult(bool success, interfaces::BlockAndHeaderTipInfo tip_info);
    /// Request core shutdown
    void requestShutdown();
    /// Handle runaway exceptions. Shows a message box with the problem and quits the program.
    void handleRunawayException(const QString& message);

    /// Show non-fatal exception details
    void handleNonFatalException(const QString& message);

Q_SIGNALS:
    void requestedInitialize();
    void requestedShutdown();
    void windowShown(HRBJackpotCoinGUI* window);

protected:
    bool event(QEvent* e) override;

private:
    void startThread();

    std::optional<InitExecutor> m_executor;
    OptionsModel* optionsModel{nullptr};
    ClientModel* clientModel{nullptr};
    HRBJackpotCoinGUI* window{nullptr};
    QTimer* pollShutdownTimer{nullptr};
#ifdef ENABLE_WALLET
    PaymentServer* paymentServer{nullptr};
    WalletController* m_wallet_controller{nullptr};
#endif
    const PlatformStyle* platformStyle{nullptr};
    std::unique_ptr<QWidget> shutdownWindow;
    SplashScreen* m_splash{nullptr};
    std::unique_ptr<interfaces::Node> m_node;
};

int GuiMain(int argc, char* argv[]);

#endif // HRBJACKPOTCOIN_QT_HRBJACKPOTCOIN_H
