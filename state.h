#ifndef STATE_H
#define STATE_H

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <functional>
#include "params.h"


typedef struct {
    int64_t stack[MAX_STACK];
    uint8_t depth;

    int64_t x;
    int64_t y;

    bool x_init;
    bool y_init;
} State;

inline bool identical(const State *s, const State *t) {
    return s->depth == t->depth &&
        s->x_init == t->x_init && (!s->x_init || s->x == t->x) &&
        s->y_init == t->y_init && (!s->y_init || s->y == t->y) &&
        memcmp(s->stack, t->stack, s->depth * sizeof s->stack[0]) == 0;
}

struct StatesHash {
    size_t operator()(const State *states) const noexcept {
        const std::hash<int64_t> hash_value{};
        size_t hash = 0;

        for (size_t i = 0; i < NUM_INPUTS; i++) {
            const State &state = states[i];
            hash = 31 * hash + hash_value(state.depth);
            for (size_t j = 0; j < state.depth; j++) {
                hash = 31 * hash + hash_value(state.stack[j]);
            }
            hash = 31 * hash + hash_value(state.x_init);
            hash = 31 * hash + (state.x_init ? hash_value(state.x) : 0);
            hash = 31 * hash + hash_value(state.y_init);
            hash = 31 * hash + (state.y_init ? hash_value(state.y) : 0);
        }
        return hash;
    }
};

struct StatesEqual {
    bool operator()(const State *a, const State *b) const noexcept {
        for (size_t i = 0; i < NUM_INPUTS; i++) {
            if (!identical(&a[i], &b[i])) {
                return false;
            }
        }
        return true;
    }
};


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

inline uint64_t opcode(const char* name) {
    uint64_t opcode = 0;
    for (size_t i = 0; i < strlen(name); i++) {
        opcode <<= 8;
        opcode += name[i];
    }

    return opcode;
}


typedef struct Node {
    State states[NUM_INPUTS];
    Node *parent;
    Op op;
} Node;

static inline bool matches_targets(const Node *node) {
    for (size_t k = 0; k < NUM_INPUTS; k++) {
        const State *state = &node->states[k];

        if (state->depth == 0 ||
            !match_output(state->stack[state->depth - 1], targets[k])) {
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
