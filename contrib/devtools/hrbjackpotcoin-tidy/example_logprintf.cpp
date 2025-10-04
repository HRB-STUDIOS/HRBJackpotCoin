// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <string>

// Test for hrbjackpotcoin-unterminated-logprintf

enum LogFlags {
    NONE
};

enum Level {
    None
};

template <typename... Args>
static inline void LogPrintf_(const std::string& logging_function, const std::string& source_file, const int source_line, const LogFlags flag, const Level level, const char* fmt, const Args&... args)
{
}

#define LogPrintLevel_(category, level, ...) LogPrintf_(__func__, __FILE__, __LINE__, category, level, __VA_ARGS__)
#define LogPrintf(...) LogPrintLevel_(LogFlags::NONE, Level::None, __VA_ARGS__)

#define LogPrint(category, ...) \
    do {                        \
        LogPrintf(__VA_ARGS__); \
    } while (0)


class CWallet
{
    std::string GetDisplayName() const
    {
        return "default wallet";
    }

public:
    template <typename... Params>
    void WalletLogPrintf(const char* fmt, Params... parameters) const
    {
        LogPrintf(("%s " + std::string{fmt}).c_str(), GetDisplayName(), parameters...);
    };
};

struct ScriptPubKeyMan
{
    std::string GetDisplayName() const
    {
        return "default wallet";
    }

    template <typename... Params>
    void WalletLogPrintf(const char* fmt, Params... parameters) const
    {
        LogPrintf(("%s " + std::string{fmt}).c_str(), GetDisplayName(), parameters...);
    };
};

void good_func()
{
    LogPrintf("hello world!\n");
}
void good_func2()
{
    CWallet wallet;
    wallet.WalletLogPrintf("hi\n");
    ScriptPubKeyMan spkm;
    spkm.WalletLogPrintf("hi\n");

    const CWallet& walletref = wallet;
    walletref.WalletLogPrintf("hi\n");

    auto* walletptr = new CWallet();
    walletptr->WalletLogPrintf("hi\n");
    delete walletptr;
}
void bad_func()
{
    LogPrintf("hello world!");
}
void bad_func2()
{
    LogPrintf("");
}
void bad_func3()
{
    // Ending in "..." has no special meaning.
    LogPrintf("hello world!...");
}
void bad_func4_ignored()
{
    LogPrintf("hello world!"); // NOLINT(hrbjackpotcoin-unterminated-logprintf)
}
void bad_func5()
{
    CWallet wallet;
    wallet.WalletLogPrintf("hi");
    ScriptPubKeyMan spkm;
    spkm.WalletLogPrintf("hi");

    const CWallet& walletref = wallet;
    walletref.WalletLogPrintf("hi");

    auto* walletptr = new CWallet();
    walletptr->WalletLogPrintf("hi");
    delete walletptr;
}
