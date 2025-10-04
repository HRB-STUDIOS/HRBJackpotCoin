// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_SHUTDOWN_H
#define HRBJACKPOTCOIN_SHUTDOWN_H

/** Request shutdown of the application. */
void StartShutdown();

/** Clear shutdown flag. Only use this during init (before calling WaitForShutdown in any
 * thread), or in the unit tests. Calling it in other circumstances will cause a race condition.
 */
void AbortShutdown();

/** Returns true if a shutdown is requested, false otherwise. */
bool ShutdownRequested();

/** Wait for StartShutdown to be called in any thread. This can only be used
 * from a single thread.
 */
void WaitForShutdown();

#endif // HRBJACKPOTCOIN_SHUTDOWN_H
