#include "assert.h"
#include "kernel_stdio.h"

void __assert_fail(const char* expr, const char* file, unsigned int line) { // NOLINT(*-reserved-identifier)
    kfprintf(kstderr, "Assertion failed: %s, file %s, line %d\n", expr, file, line);
}

void __assert_fail_msg(const char* expr, const char* message, const char* file, unsigned int line) { // NOLINT(*-reserved-identifier)
    kfprintf(kstderr, "Message: %s", message);
    kfprintf(kstderr, "Assertion failed: %s, file %s, line %d\n", expr, file, line);
}