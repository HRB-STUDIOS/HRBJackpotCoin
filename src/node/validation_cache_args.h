// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_NODE_VALIDATION_CACHE_ARGS_H
#define HRBJACKPOTCOIN_NODE_VALIDATION_CACHE_ARGS_H

class ArgsManager;
namespace kernel {
struct ValidationCacheSizes;
};

namespace node {
void ApplyArgsManOptions(const ArgsManager& argsman, kernel::ValidationCacheSizes& cache_sizes);
} // namespace node

#endif // HRBJACKPOTCOIN_NODE_VALIDATION_CACHE_ARGS_H
