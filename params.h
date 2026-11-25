#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

#define MAX_STACK 16
#define MAX_LENGTH 7
// Int literals from 0..MAX_LITERAL inclusive
#define MAX_LITERAL 9

static_assert(MAX_LENGTH >= 1, "MAX_LENGTH must be at least 1");
static_assert(MAX_LITERAL <= INT64_MAX,
    "MAX_LITERAL > INT64_MAX, this is not allowed as the calculations use int64_t");


static constexpr int64_t inputs[] = {
    1,2,3
};

static constexpr int64_t targets[] = {
    2,65,730
};

#define NUM_INPUTS (sizeof inputs / sizeof inputs[0])
static_assert(sizeof targets / sizeof targets[0] == NUM_INPUTS,
              "Input array length doesn't match target array length");

constexpr const char* OPS[] = {
    "+",
    "-",
    "*",
    // "/",
    "^",
    "v",
    "c",
    "X",
    "x",
    // "|6",
    // ":t"
};

#define NUM_OPS (sizeof OPS / sizeof OPS[0])


#endif
