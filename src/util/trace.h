// Copyright (c) 2025 HRB Studios
// HRB Jackpot Coin™ is a trademark of HRB Studios. All rights reserved.
// Distributed under the MIT software license, see the accompanying LICENSE file or visit https://opensource.org/licenses/MIT
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HRBJACKPOTCOIN_UTIL_TRACE_H
#define HRBJACKPOTCOIN_UTIL_TRACE_H

#if defined(HAVE_CONFIG_H)
#include <config/hrbjackpotcoin-config.h>
#endif

#ifdef ENABLE_TRACING

#include <sys/sdt.h>

// Disabling this warning can be removed once we switch to C++20
#if defined(__clang__) && __cplusplus < 202002L
#define HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH _Pragma("clang diagnostic push") _Pragma("clang diagnostic ignored \"-Wgnu-zero-variadic-macro-arguments\"")
#define HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP _Pragma("clang diagnostic pop")
#else
#define HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH
#define HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#endif

#define TRACE(context, event) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE(context, event) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE1(context, event, a) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE1(context, event, a) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE2(context, event, a, b) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE2(context, event, a, b) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE3(context, event, a, b, c) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE3(context, event, a, b, c) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE4(context, event, a, b, c, d) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE4(context, event, a, b, c, d) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE5(context, event, a, b, c, d, e) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE5(context, event, a, b, c, d, e) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE6(context, event, a, b, c, d, e, f) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE6(context, event, a, b, c, d, e, f) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE7(context, event, a, b, c, d, e, f, g) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE7(context, event, a, b, c, d, e, f, g) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE8(context, event, a, b, c, d, e, f, g, h) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE8(context, event, a, b, c, d, e, f, g, h) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE9(context, event, a, b, c, d, e, f, g, h, i) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE9(context, event, a, b, c, d, e, f, g, h, i) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE10(context, event, a, b, c, d, e, f, g, h, i, j) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE10(context, event, a, b, c, d, e, f, g, h, i, j) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE11(context, event, a, b, c, d, e, f, g, h, i, j, k) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE11(context, event, a, b, c, d, e, f, g, h, i, j, k) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP
#define TRACE12(context, event, a, b, c, d, e, f, g, h, i, j, k, l) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_PUSH DTRACE_PROBE12(context, event, a, b, c, d, e, f, g, h, i, j, k, l) HRBJACKPOTCOIN_DISABLE_WARN_ZERO_VARIADIC_POP

#else

#define TRACE(context, event)
#define TRACE1(context, event, a)
#define TRACE2(context, event, a, b)
#define TRACE3(context, event, a, b, c)
#define TRACE4(context, event, a, b, c, d)
#define TRACE5(context, event, a, b, c, d, e)
#define TRACE6(context, event, a, b, c, d, e, f)
#define TRACE7(context, event, a, b, c, d, e, f, g)
#define TRACE8(context, event, a, b, c, d, e, f, g, h)
#define TRACE9(context, event, a, b, c, d, e, f, g, h, i)
#define TRACE10(context, event, a, b, c, d, e, f, g, h, i, j)
#define TRACE11(context, event, a, b, c, d, e, f, g, h, i, j, k)
#define TRACE12(context, event, a, b, c, d, e, f, g, h, i, j, k, l)

#endif


#endif // HRBJACKPOTCOIN_UTIL_TRACE_H
