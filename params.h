#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

#define MAX_LENGTH 7

// Set to 0 for automatic worst-case
#define MAX_STACK 0
// Worst case is "cbbb..."
#if MAX_STACK == 0
    #undef MAX_STACK
    #define MAX_STACK (2 * MAX_LENGTH)
#endif

// Int literals from 0..MAX_LITERAL inclusive
#define MAX_LITERAL 9


static constexpr int64_t inputs[] = {
    1,2,3
};

static constexpr int64_t targets[] = {
    2,65,730
};

inline bool match_output(int64_t actual, int64_t target) {
    return actual == target;
}

constexpr const char* OPS[] = {
    "+",
    "-",
    "*",
    "/",
    "^",
    "v",
    "c",
    "X",
    "x",
    // "#",
    // ":C",
    // ":G"
};


static_assert(MAX_LENGTH >= 1, "MAX_LENGTH must be at least 1");
static_assert(MAX_LITERAL <= INT64_MAX,
    "MAX_LITERAL > INT64_MAX, this is not allowed as the calculations use int64_t");

#define NUM_INPUTS std::size(inputs)
static_assert(std::size(targets) == NUM_INPUTS,
              "Input array length doesn't match target array length");

#define NUM_OPS (sizeof OPS / sizeof OPS[0])


#endif
