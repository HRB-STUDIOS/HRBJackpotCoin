// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.

#include <univalue.h>
#include <rpc/server.h>
#include <chainparams.h>
#include <validation.h>
#include <consensus/amount.h>
#include <util/moneystr.h>
#include <node/context.h>
#include <node/chainstate.h>
#include <util/translation.h>

#define ARRAYLEN(array) (sizeof(array)/sizeof((array)[0]))

static UniValue getjackpotpools(const JSONRPCRequest& request)
{
    // NOTE: This RPC is a placeholder. The `CBlockIndex` structure does not
    //       yet contain jackpot pool balances.
    //       This RPC is only functional for demonstration purposes and will
    //       return dummy values.

    const NodeContext& node = EnsureNodeContext(request.context);
    ChainstateManager& chainman = EnsureChainman(node);

    // The RPC needs to get the current state, so we lock the main chain mutex.
    // This is a corrected way to access the active chain tip safely.
    const CBlockIndex* pindex = WITH_LOCK(chainman.GetMutex(), return chainman.ActiveChain().Tip());

    if (!pindex) {
        throw JSONRPCError(RPC_MISC_ERROR, "No active chain tip.");
    }

    UniValue result(UniValue::VOBJ);

    // Placeholder values for now, as CBlockIndex does not have nJackpotMini etc.
    // To make this fully functional, CBlockIndex would need to be extended.
    result.pushKV("mini", FormatMoney(CAmount(1234500000000))); // 12,345 HRB
    result.pushKV("minor", FormatMoney(CAmount(5678900000000))); // 56,789 HRB
    result.pushKV("major", FormatMoney(CAmount(10000000000000))); // 100,000 HRB
    result.pushKV("grand", FormatMoney(CAmount(50000000000000))); // 500,000 HRB

    return result;
}

// The CRPCCommand struct is initialized with the name, category,
// function pointer, argument names, and an empty UniValue object for help.
static const CRPCCommand commands[] = {
    { "jackpot", "getjackpotpools", &getjackpotpools, {""}, RPC_MISC },
};

void RegisterJackpotRPCCommands(CRPCTable& t)
{
    for (unsigned int vcidx = 0; vcidx < ARRAYLEN(commands); vcidx++)
        t.appendCommand(commands[vcidx].name, &commands[vcidx]);
}