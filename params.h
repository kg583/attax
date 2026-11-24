#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

#define MAX_STACK 16
#define MAX_LENGTH 4
// Int literals from 0..MAX_LITERAL inclusive
#define MAX_LITERAL 9

static_assert(MAX_LITERAL <= INT64_MAX,
    "MAX_LITERAL > INT64_MAX, this is not allowed as the calaculations use int64_t");


#define NUM_INPUTS (sizeof inputs / sizeof inputs[0])
#define NUM_OPS (sizeof OPS / sizeof OPS[0])



static const int64_t inputs[] = {
    0,1,2
};

static const int64_t targets[] = {
    1,2,3
};

static_assert(sizeof targets / sizeof targets[0] == NUM_INPUTS,
              "Input array length doesn't match target array length");

static const uint64_t OPS[] = {
    '+',
    '-',
    '*',
    // '/',
    '^',
    'v',
    'c'
};


#endif
