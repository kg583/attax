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
    uint64_t opcode;
    bool is_number;
} Op;

// TODO: maybe make this faster? Made it generic for now incase we implement macros (E|+)
inline uint8_t length(const Op op) {
    const uint64_t base = op.is_number ? 10 : 256;
    uint8_t count = 1;

    for (uint64_t value = op.opcode; value >= base; value /= base) {
        count++;
    }

    return count;
}


typedef struct Node {
    State states[NUM_INPUTS];
    struct Node *parent;
    Op op;
} Node;

static inline bool matches_targets(const Node *node) {
    for (size_t k = 0; k < NUM_INPUTS; k++) {
        const State *state = &node->states[k];

        if (state->depth == 0 ||
            state->stack[state->depth - 1] != targets[k]) {
            return false;
        }
    }

    return true;
}


typedef struct {
    Node **nodes;
    size_t count;
    size_t capacity;
} CacheLevel;



#endif
