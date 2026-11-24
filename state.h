#ifndef STATE_H
#define STATE_H

#include <math.h>
#include <stdint.h>
#include <string.h>
#include "params.h"


typedef struct {
    int64_t stack[MAX_STACK];
    uint8_t depth;

    int64_t x;
    int64_t y;
} State;

inline bool identical(const State *s, const State *t) {
    return (s->depth == t->depth) && (s->x == t->x) && (s->y == t-> y) &&
        (memcmp(s->stack, t->stack, s->depth) == 0);
}


typedef struct {
    int64_t opcode;
    bool is_number;
} Op;

inline uint8_t length(Op op) {
    if (op.opcode == 0) return 1;
    return ceill(op.is_number ? log10l(op.opcode) : log2l(op.opcode) / 8);
}


typedef struct Node {
    State states[NUM_INPUTS];
    struct Node *parent;
    Op op;
} Node;


typedef struct {
    Node **nodes;
    size_t count;
    size_t capacity;
} CacheLevel;



#endif
