#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include "state.h"


bool add(int64_t a, int64_t b, int64_t &result);
bool sub(int64_t a, int64_t b, int64_t &result);
bool mul(int64_t a, int64_t b, int64_t &result);
bool div_floor(int64_t a, int64_t b, int64_t &result);
bool mod(int64_t a, int64_t b, int64_t &result);
bool pow_floor(int64_t a, int64_t b, int64_t &result);
bool inc(int64_t a, int64_t &result);
bool dec(int64_t a, int64_t &result);
bool halve(int64_t a, int64_t &result);
bool unhalve(int64_t a, int64_t &result);
bool bit_and(int64_t a, int64_t b, int64_t &result);
bool bit_or(int64_t a, int64_t b, int64_t &result);
bool bit_xor(int64_t a, int64_t b, int64_t &result);
bool square(int64_t a, int64_t &result);
bool negate(int64_t a, int64_t &result);
bool abs_value(int64_t a, int64_t &result);
bool min(int64_t a, int64_t b, int64_t &result);
bool max(int64_t a, int64_t b, int64_t &result);

bool logical_not(int64_t a, int64_t &result);
bool less(int64_t a, int64_t b, int64_t &result);
bool greater(int64_t a, int64_t b, int64_t &result);
bool equal(int64_t a, int64_t b, int64_t &result);

bool div_all(int64_t a, int64_t b, int64_t &result);
bool shift_left(int64_t a, int64_t b, int64_t &result);
bool shift_right(int64_t a, int64_t b, int64_t &result);
bool parity_sign(int64_t a, int64_t &result);
bool two_power(int64_t a, int64_t &result);
bool nth_fib(int64_t a, int64_t &result);
bool nth_prime(int64_t a, int64_t &result);
bool ten_power(int64_t a, int64_t &result);
bool choose(int64_t a, int64_t b, int64_t &result);
bool is_even(int64_t a, int64_t &result);
bool factorial(int64_t a, int64_t &result);
bool gcd(int64_t a, int64_t b, int64_t &result);
bool lcm(int64_t a, int64_t b, int64_t &result);
bool int_nth_root(int64_t a, int64_t b, int64_t &result);
bool is_prime(int64_t a, int64_t &result);
bool int_sqrt(int64_t a, int64_t &result);
bool set_interior(int64_t a, int64_t &result);
bool coprime(int64_t a, int64_t b, int64_t &result);
bool abs_diff(int64_t a, int64_t b, int64_t &result);
bool get_bit(int64_t a, int64_t b, int64_t &result);
bool unset_bit(int64_t a, int64_t b, int64_t &result);
bool set_bit(int64_t a, int64_t b, int64_t &result);
bool toggle_bit(int64_t a, int64_t b, int64_t &result);
bool multiplicity(int64_t a, int64_t b, int64_t &result);
bool sign(int64_t a, int64_t &result);
bool popcount(int64_t a, int64_t &result);
bool floor_log_2(int64_t a, int64_t &result);
bool floor_log_10(int64_t a, int64_t &result);
bool between(int64_t a, int64_t b, int64_t c, int64_t &result);
bool clamp(int64_t a, int64_t b, int64_t c, int64_t &result);
bool catalan(int64_t a, int64_t &result);
bool low_bit(int64_t a, int64_t &result);
bool high_bit(int64_t a, int64_t &result);

bool next_multiple(int64_t a, int64_t b, int64_t &result);
bool is_power(int64_t a, int64_t b, int64_t &result);
bool last_prime(int64_t a, int64_t &result);
bool next_prime(int64_t a, int64_t &result);
bool totient(int64_t a, int64_t &result);


bool alter_stack(State *state);
bool both_copy(State *state);
bool copy(State *state);
bool discard(State *state);
bool next(State *state);
bool under(State *state);
bool swap(State *state);

bool push(State *state, int64_t);
bool tuck(State *state, int64_t);
bool unary(State *state, bool (*)(int64_t, int64_t &result));
bool binary(State *state, bool (*)(int64_t, int64_t, int64_t &result));
bool ternary(State *state, bool (*)(int64_t, int64_t, int64_t, int64_t &result));

bool X(State* state);
bool Y(State* state);
bool x(State* state);
bool y(State* state);

bool divmod(State *state);
bool square_two(State *state);


#endif
