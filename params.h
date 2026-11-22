#ifndef PARAMS_H
#define PARAMS_H

#include <stdint.h>

#define MAX_STACK 16
#define MAX_LENGTH 4
#define NUM_INPUTS (sizeof inputs / sizeof inputs[0])
#define NUM_OPS (sizeof OPS / sizeof OPS[0])

static const int64_t inputs[] = {
    0
};

static const int64_t targets[] = {
    1
};

static_assert(sizeof targets / sizeof targets[0] == NUM_INPUTS,
              "Input array length doesn't match target array length");

static const int64_t OPS[] = {
    '+',
    '-',
    '*',
    '/',
    '^',
    'v'
};

// Int literals from 0..MAX_LITERAL inclusive
static const int64_t MAX_LITERAL = 9;

#endif
