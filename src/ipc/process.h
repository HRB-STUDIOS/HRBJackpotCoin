// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_IPC_PROCESS_H
#define HRBJACKPOTCOIN_IPC_PROCESS_H

#include <util/fs.h>

#include <memory>
#include <string>

namespace ipc {
class Protocol;

//! IPC process interface for spawning hrbjackpotcoin processes and serving requests
//! in processes that have been spawned.
//!
//! There will be different implementations of this interface depending on the
//! platform (e.g. unix, windows).
class Process
{
public:
    virtual ~Process() = default;

    //! Spawn process and return socket file descriptor for communicating with
    //! it.
    virtual int spawn(const std::string& new_exe_name, const fs::path& argv0_path, int& pid) = 0;

    //! Wait for spawned process to exit and return its exit code.
    virtual int waitSpawned(int pid) = 0;

    //! Parse command line and determine if current process is a spawned child
    //! process. If so, return true and a file descriptor for communicating
    //! with the parent process.
    virtual bool checkSpawned(int argc, char* argv[], int& fd) = 0;
};

//! Constructor for Process interface. Implementation will vary depending on
//! the platform (unix or windows).
std::unique_ptr<Process> MakeProcess();
} // namespace ipc

#endif // HRBJACKPOTCOIN_IPC_PROCESS_H
