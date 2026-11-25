#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>
#include "state.h"


int64_t add(int64_t a, int64_t b);
int64_t sub(int64_t a, int64_t b);
int64_t mul(int64_t a, int64_t b);
int64_t div_floor(int64_t a, int64_t b);
int64_t mod(int64_t a, int64_t b);
int64_t pow_floor(int64_t a, int64_t b);
int64_t inc(int64_t a);
int64_t dec(int64_t a);
int64_t halve(int64_t a);
int64_t unhalve(int64_t a);
int64_t bit_and(int64_t a, int64_t b);
int64_t bit_or(int64_t a, int64_t b);
int64_t bit_xor(int64_t a, int64_t b);
int64_t square(int64_t a);
int64_t negate(int64_t a);
int64_t min(int64_t a, int64_t b);
int64_t max(int64_t a, int64_t b);

int64_t logical_not(int64_t a);
int64_t less(int64_t a, int64_t b);
int64_t greater(int64_t a, int64_t b);
int64_t equal(int64_t a, int64_t b);

int64_t div_all(int64_t a, int64_t b);
int64_t shift_left(int64_t a, int64_t b);
int64_t shift_right(int64_t a, int64_t b);
int64_t parity_sign(int64_t a);
int64_t two_power(int64_t a);
int64_t nth_fib(int64_t a);
int64_t nth_prime(int64_t a);
int64_t ten_power(int64_t a);
int64_t choose(int64_t a, int64_t b);
int64_t is_even(int64_t a);
int64_t factorial(int64_t a);
int64_t gcd(int64_t a, int64_t b);
int64_t lcm(int64_t a, int64_t b);
int64_t int_nth_root(int64_t a, int64_t b);
int64_t is_prime(int64_t a);
int64_t int_sqrt(int64_t a);
int64_t set_interior(int64_t a);
int64_t coprime(int64_t a, int64_t b);
int64_t abs_diff(int64_t a, int64_t b);
int64_t get_bit(int64_t a, int64_t b);
int64_t unset_bit(int64_t a, int64_t b);
int64_t set_bit(int64_t a, int64_t b);
int64_t toggle_bit(int64_t a, int64_t b);
int64_t multiplicity(int64_t a, int64_t b);
int64_t sign(int64_t a);
int64_t popcount(int64_t a);
int64_t floor_log_2(int64_t a);
int64_t floor_log_10(int64_t a);
int64_t between(int64_t a, int64_t b, int64_t c);
int64_t clamp(int64_t a, int64_t b, int64_t c);
int64_t catalan(int64_t a);
int64_t low_bit(int64_t a);
int64_t high_bit(int64_t a);

int64_t next_multiple(int64_t a, int64_t b);
int64_t is_power(int64_t a, int64_t b);
int64_t last_prime(int64_t a);
int64_t next_prime(int64_t a);
int64_t totient(int64_t a);


bool alter_stack(State *state);
bool both_copy(State *state);
bool copy(State *state);
bool discard(State *state);
bool next(State *state);
bool under(State *state);
bool swap(State *state);

bool push(State *state, int64_t);
bool tuck(State *state, int64_t);
bool unary(State *state, int64_t (*op)(int64_t));
bool binary(State *state, int64_t (*op)(int64_t, int64_t));
bool ternary(State *state, int64_t (*op)(int64_t, int64_t, int64_t));

bool X(State* state);
bool Y(State* state);
bool x(State* state);
bool y(State* state);

bool divmod(State *state);
bool square_two(State *state);


#endif
