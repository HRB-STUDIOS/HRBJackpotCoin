// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_NETMESSAGEMAKER_H
#define HRBJACKPOTCOIN_NETMESSAGEMAKER_H

#include <net.h>
#include <serialize.h>

class CNetMsgMaker
{
public:
    explicit CNetMsgMaker(int nVersionIn) : nVersion(nVersionIn){}

    template <typename... Args>
    CSerializedNetMsg Make(int nFlags, std::string msg_type, Args&&... args) const
    {
        CSerializedNetMsg msg;
        msg.m_type = std::move(msg_type);
        CVectorWriter{nFlags | nVersion, msg.data, 0, std::forward<Args>(args)...};
        return msg;
    }

    template <typename... Args>
    CSerializedNetMsg Make(std::string msg_type, Args&&... args) const
    {
        return Make(0, std::move(msg_type), std::forward<Args>(args)...);
    }

private:
    const int nVersion;
};

#endif // HRBJACKPOTCOIN_NETMESSAGEMAKER_H
