#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <vector>

#include "ops.h"
#include "params.h"
#include "state.h"


static bool execute(State *state, const Op op) {
    if (op.is_number) {
        push(state, static_cast<int64_t>(op.opcode));
        return true;
    }

    switch (op.opcode) {

    case 0x23: return binary(state, pow_floor);
    case 0x25: return binary(state, mod);
    case 0x2A: return binary(state, mul);
    case 0x2B: return binary(state, add);
    case 0x2D: return binary(state, sub);
    case 0x2F: return binary(state, div_floor);
    case 0x4A: return unary(state, square);
    case 0x48: return unary(state, unhalve);
    case 0x49: return binary(state, bit_and);
    case 0x4D: return binary(state, bit_or);
    case 0x4E: return unary(state, negate);
    case 0x4F: return tuck(state, 1);
    case 0x53: return binary(state, bit_xor);
    case 0x54: return binary(state, max);
    case 0x55: return push(state, -1);
    case 0x5A: return tuck(state, 0);
    case 0x5E: return unary(state, inc);
    case 0x68: return unary(state, halve);
    case 0x74: return binary(state, min);
    case 0x76: return unary(state, dec);

    case 0x21: return unary(state, logical_not);
    case 0x3C: return binary(state, less);
    case 0x3D: return binary(state, equal);
    case 0x3E: return binary(state, greater);

    case 0x5B: return under(state);
    case 0x61: return alter_stack(state);
    case 0x62: return both_copy(state);
    case 0x63: return copy(state);
    case 0x64: return discard(state);
    case 0x6E: return next(state);
    case 0x73: return swap(state);

    case 0x58: return X(state);
    case 0x59: return Y(state);
    case 0x78: return x(state);
    case 0x79: return y(state);

    case 0x3A21: return binary(state, coprime);
    case 0x3A2B: return unary(state, sign);
    case 0x3A2D: return binary(state, abs_diff);
    case 0x3A2F: return binary(state, multiplicity);
    case 0x3A31: return unary(state, popcount);
    case 0x3A32: return unary(state, floor_log_2);
    case 0x3A3A: return binary(state, toggle_bit);
    case 0x3A40: return binary(state, get_bit);
    case 0x3A41: return unary(state, floor_log_10);
    case 0x3A47: return unary(state, high_bit);
    case 0x3A4A: return square_two(state);
    case 0x3A4E: return binary(state, is_power);
    case 0x3A50: return unary(state, next_prime);
    case 0x3A5B: return binary(state, unset_bit);
    case 0x3A5D: return binary(state, set_bit);
    case 0x3A62: return ternary(state, between);
    case 0x3A63: return ternary(state, clamp);
    case 0x3A67: return unary(state, low_bit);
    case 0x3A6D: return binary(state, next_multiple);
    case 0x3A70: return unary(state, last_prime);
    case 0x3A74: return unary(state, totient);
    case 0x3A7E: return unary(state, set_interior);

    case 0x7C25: return divmod(state);
    case 0x7C2F: return binary(state, div_all);
    case 0x7C31: return unary(state, parity_sign);
    case 0x7C32: return unary(state, two_power);
    case 0x7C35: return unary(state, nth_fib);
    case 0x7C36: return unary(state, nth_prime);
    case 0x7C3C: return binary(state, shift_left);
    case 0x7C3E: return binary(state, shift_right);
    case 0x7C41: return unary(state, ten_power);
    // case 0x7C43: return binary(state, choose);
    // case 0x7C46: return unary(state, factorial);
    case 0x7C6E: return binary(state, int_nth_root);
    case 0x7C61: return unary(state, std::abs);
    case 0x7C65: return unary(state, is_even);
    case 0x7C67: return binary(state, gcd);
    case 0x7C6C: return binary(state, lcm);
    case 0x7C70: return unary(state, is_prime);
    case 0x7C71: return unary(state, int_sqrt);

    default:
        return false;
    }
}

static void print_source(const Node *node) {
    Op instructions[MAX_LENGTH];
    size_t count = 0;

    for (; node->parent; node = node->parent) {
        instructions[count++] = node->op;
    }

    while (count > 0) {
        const Op op = instructions[--count];

        if (op.is_number) {
            printf("%zu", op.opcode);
        } else {
            // Print each char one at a time
            for (int shift = 8 * (length(op) - 1); shift >= 0; shift -= 8) {
                putchar((op.opcode >> shift) & UINT8_MAX);
            }
        }
    }

    putchar('\n');
}


int main() {
    std::vector<Op> OPCODES[MAX_LENGTH + 1];

    // Build ops
    for (const char *name : OPS) {
        Op op;
        op.opcode = opcode(name);
        op.is_number = false;
        const int op_length = length(op);
        if (op_length <= MAX_LENGTH) {
            OPCODES[op_length].push_back(op);
        }
    }

    // Build int literals
    for (uint64_t literal = 0; literal <= MAX_LITERAL; literal++) {
        Op op;
        op.opcode = literal;
        op.is_number = true;
        const int op_length = length(op);
        if (op_length > MAX_LENGTH) break;
        OPCODES[op_length].push_back(op);
    }

    CacheLevel cache[MAX_LENGTH + 1] = {};
    std::unordered_set<const State*, StatesHash, StatesEqual> seen;

    // Initialise root
    Node *root = static_cast<Node*>(calloc(1, sizeof(Node)));
    if (!root) {
        return EXIT_FAILURE;
    }

    // Initialise root state
    for (size_t i = 0; i < NUM_INPUTS; i++) {
        root->states[i].depth = 1;
        root->states[i].stack[0] = inputs[i];
        root->states[i].x_init = false;
        root->states[i].y_init = false;
    }

    // Initialise cache
    cache[0].nodes = static_cast<Node**>(malloc(sizeof(Node*)));
    if (!cache[0].nodes) {
        free(root);
        return EXIT_FAILURE;
    }

    cache[0].nodes[0] = root;
    cache[0].count = 1;
    cache[0].capacity = 1;

    int result = EXIT_SUCCESS;

    seen.insert(root->states);

    for (int n = 1; n <= MAX_LENGTH; n++) {
        CacheLevel *level = &cache[n];

        for (int op_length = 1; op_length <= n; op_length++) {
            const std::vector<Op> &ops = OPCODES[op_length];
            if (ops.empty()) continue;

            const CacheLevel *parents = &cache[n - op_length];
            for (size_t i = 0; i < parents->count; i++) {
                Node *parent = parents->nodes[i];

                for (const Op op : ops) {
                    // Allocate the new node
                    Node *child = static_cast<Node*>(malloc(sizeof(Node)));

                    if (!child) {
                        result = EXIT_FAILURE;
                        goto cleanup;
                    }

                    // Initialise the child
                    *child = *parent;
                    child->parent = parent;
                    child->op = op;

                    // Execute op
                    size_t k = 0;
                    while (k < NUM_INPUTS && execute(&child->states[k], op)) {
                        k++;
                    }
                    // Reject the candidate if execution fails on any input
                    if (k < NUM_INPUTS) {
                        free(child);
                        continue;
                    }
                    
                    if (matches_targets(child)) {
                        print_source(child);
                    }

                    // Grow the cache array if necessary
                    if (level->count == level->capacity) {
                        const size_t new_capacity = level->capacity ? level->capacity * 2 : 16;

                        Node **new_nodes = static_cast<Node**>(realloc(
                            level->nodes,
                            new_capacity * sizeof(Node*)
                        ));

                        if (!new_nodes) {
                            free(child);
                            result = EXIT_FAILURE;
                            goto cleanup;
                        }

                        level->nodes = new_nodes;
                        level->capacity = new_capacity;
                    }
                    
                    // Already seen
                    if (!seen.insert(child->states).second) {
                        free(child);
                        continue;
                    }

                    // Add the child to its cache level
                    level->nodes[level->count++] = child;
                }
            }
        }
        
        printf("Length %d done (%zu expressions)\n", n, level->count);
    }


cleanup:
    // Free every node and cache array
    for (int n = 0; n <= MAX_LENGTH; n++) {
        for (size_t i = 0; i < cache[n].count; i++)
            free(cache[n].nodes[i]);

        free(cache[n].nodes);
    }

    return result;
}
