// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT

#include <common/args.h>
#include <interfaces/chain.h>
#include <interfaces/echo.h>
#include <interfaces/init.h>
#include <interfaces/ipc.h>
#include <interfaces/node.h>
#include <interfaces/wallet.h>
#include <node/context.h>
#include <util/check.h>

#include <memory>

namespace init {
namespace {
const char* EXE_NAME = "hrbjackpotcoin-node";

class HRBJackpotCoinNodeInit : public interfaces::Init
{
public:
    HRBJackpotCoinNodeInit(node::NodeContext& node, const char* arg0)
        : m_node(node),
          m_ipc(interfaces::MakeIpc(EXE_NAME, arg0, *this))
    {
        m_node.args = &gArgs;
        m_node.init = this;
    }
    std::unique_ptr<interfaces::Node> makeNode() override { return interfaces::MakeNode(m_node); }
    std::unique_ptr<interfaces::Chain> makeChain() override { return interfaces::MakeChain(m_node); }
    std::unique_ptr<interfaces::WalletLoader> makeWalletLoader(interfaces::Chain& chain) override
    {
        return MakeWalletLoader(chain, *Assert(m_node.args));
    }
    std::unique_ptr<interfaces::Echo> makeEcho() override { return interfaces::MakeEcho(); }
    interfaces::Ipc* ipc() override { return m_ipc.get(); }
    node::NodeContext& m_node;
    std::unique_ptr<interfaces::Ipc> m_ipc;
};
} // namespace
} // namespace init

namespace interfaces {
std::unique_ptr<Init> MakeNodeInit(node::NodeContext& node, int argc, char* argv[], int& exit_status)
{
    auto init = std::make_unique<init::HRBJackpotCoinNodeInit>(node, argc > 0 ? argv[0] : "");
    // Check if hrbjackpotcoin-node is being invoked as an IPC server. If so, then
    // bypass normal execution and just respond to requests over the IPC
    // channel and return null.
    if (init->m_ipc->startSpawnedProcess(argc, argv, exit_status)) {
        return nullptr;
    }
    return init;
}
} // namespace interfaces
