#pragma once
#ifdef NDEBUG
#include "mellos/kernel/kernel.h"
#endif
#define __MELLOS_ASSERT__
// Formatted output
void __assert_fail(const char* expr, const char* file, unsigned int line); // NOLINT(*-reserved-identifier)
void __assert_fail_msg(const char* expr, const char* msg, const char* file, unsigned int line); // NOLINT(*-reserved-identifier)
#ifdef NDEBUG
#define assert(x) panic();
#define assert_msg(x, msg) panic();
#else
#define assert(x) if (!(x)) __assert_fail(#x, __FILE__, __LINE__);
#define assert_msg(x, msg) if (!(x)) __assert_fail_msg(#x, msg, __FILE__, __LINE__);
#endif