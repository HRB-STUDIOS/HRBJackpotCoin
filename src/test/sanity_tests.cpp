// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <key.h>
#include <test/util/setup_common.h>
#include <util/time.h>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(sanity_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(basic_sanity)
{
  BOOST_CHECK_MESSAGE(ECC_InitSanityCheck() == true, "secp256k1 sanity test");
  BOOST_CHECK_MESSAGE(ChronoSanityCheck() == true, "chrono epoch test");
}

BOOST_AUTO_TEST_SUITE_END()
