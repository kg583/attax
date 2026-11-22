
#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "params.h"

typedef struct {
    int64_t stack[MAX_STACK][NUM_INPUTS];
    uint8_t depth;
} State;

typedef struct {
    int64_t opcode;
    bool is_number;
} Op;

typedef struct Node {
    State state;
    struct Node *parent;
    Op op;
} Node;

typedef struct {
    Node **nodes;
    size_t count;
    size_t capacity;
} CacheLevel;

#endif
