// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT

#include <common/args.h>
#include <interfaces/chain.h>
#include <interfaces/echo.h>
#include <interfaces/init.h>
#include <interfaces/node.h>
#include <interfaces/wallet.h>
#include <node/context.h>
#include <util/check.h>

#include <memory>

using node::NodeContext;

namespace init {
namespace {

class HRBJackpotCoindInit : public interfaces::Init
{
public:
    explicit HRBJackpotCoindInit(NodeContext& node) : m_node(node)
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

private:
    NodeContext& m_node;
};

} // namespace
} // namespace init

namespace interfaces {
std::unique_ptr<interfaces::Init> MakeNodeInit(node::NodeContext& node, int argc, char* argv[], int& exit_status)
{
    return std::make_unique<init::HRBJackpotCoindInit>(node);
}
} // namespace interfaces
