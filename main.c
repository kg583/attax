#include <stdint.h>
#include <stdlib.h>

#include "exec.h"
#include "params.h"
#include "state.h"


int main(void) {

    CacheLevel cache[MAX_LENGTH + 1] = {0};

    // Initialise root
    Node *root = calloc(1, sizeof(Node));
    if (!root) {
        return EXIT_FAILURE;
    }

    // Initialise root state
    for (size_t i = 0; i < NUM_INPUTS; i++) {
        root->states[i].depth = 1;
        root->states[i].stack[0] = inputs[i];
    }

    // Initialise cache
    cache[0].nodes = malloc(sizeof(Node *));
    if (!cache[0].nodes) {
        free(root);
        return EXIT_FAILURE;
    }

    cache[0].nodes[0] = root;
    cache[0].count = 1;
    cache[0].capacity = 1;

    int result = EXIT_SUCCESS;

    for (int n = 0; n < MAX_LENGTH; n++) {
        CacheLevel *current = &cache[n];

        for (size_t i = 0; i < current->count; i++) {
            Node *parent = current->nodes[i];

            for (size_t j = 0; j < NUM_OPS + (size_t)MAX_LITERAL + 1; j++) {
                // Get either an operator or an integer literal
                Op op;

                if (j < NUM_OPS) {
                    op.opcode = OPS[j];
                    op.is_number = false;
                } else {
                    op.opcode = j - NUM_OPS;
                    op.is_number = true;
                }

                const int new_length = n + length(op);

                // Skip programs exceeding the limit
                if (new_length > MAX_LENGTH)
                    continue;

                // Allocate the new node
                Node *child = malloc(sizeof(Node));

                if (!child) {
                    result = EXIT_FAILURE;
                    goto cleanup;
                }

                // Initialise the child
                *child = *parent;
                child->parent = parent;

                // Execute instruction
                for (size_t k = 0; k < NUM_INPUTS; k++) {
                    execute(&child->states[k], op);
                }

                // TODO: Hash and deduplicate the state

                CacheLevel *level = &cache[new_length];

                // Grow the cache array if necessary
                if (level->count == level->capacity) {
                    const size_t new_capacity = level->capacity ? level->capacity * 2 : 16;

                    Node **new_nodes = realloc(
                        level->nodes,
                        new_capacity * sizeof(Node *)
                    );

                    if (!new_nodes) {
                        free(child);
                        result = EXIT_FAILURE;
                        goto cleanup;
                    }

                    level->nodes = new_nodes;
                    level->capacity = new_capacity;
                }

                // Add the child to its cache level
                level->nodes[level->count++] = child;

                // TODO: Check whether the output matches and reconstruct source using parent pointers and print
            }
        }
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
