#include <cmath>
#include <numeric>
#include <stdlib.h>
#include "ops.h"
#include "primes.h"


bool add(const int64_t a, const int64_t b, int64_t &result) {
    return a + b;
}

bool sub(const int64_t a, const int64_t b, int64_t &result) {
    return a - b;
}

bool mul(const int64_t a, const int64_t b, int64_t &result) {
    return a * b;
}

bool div_floor(const int64_t a, const int64_t b, int64_t &result) {
    return (a + (a < 0)) / b - (a < 0);
}

bool mod(const int64_t a, const int64_t b, int64_t &result) {
    return a % b;
}

bool pow_floor(const int64_t a, const int64_t b, int64_t &result) {
    return std::pow(a, b);
}

bool inc(const int64_t a, int64_t &result) {
    return a + 1;
}

bool dec(const int64_t a, int64_t &result) {
    return a - 1;
}

bool halve(const int64_t a, int64_t &result) {
    return a / 2;
}

bool unhalve(const int64_t a, int64_t &result) {
    return a * 2;
}

bool bit_and(const int64_t a, const int64_t b, int64_t &result) {
    return a & b;
}

bool bit_or(const int64_t a, const int64_t b, int64_t &result) {
    return a | b;
}

bool bit_xor(const int64_t a, const int64_t b, int64_t &result) {
    return a ^ b;
}

bool square(const int64_t a, int64_t &result) {
    return a * a;
}

bool negate(const int64_t a, int64_t &result) {
    return -a;
}

bool abs_value(const int64_t a, int64_t &result) {
    result = std::abs(a);
    return true;
}

bool min(const int64_t a, const int64_t b, int64_t &result) {
    return std::min(a, b);
}

bool max(const int64_t a, const int64_t b, int64_t &result) {
    return std::max(a, b);
}


bool logical_not(const int64_t a, int64_t &result) {
    return !a;
}

bool less(const int64_t a, const int64_t b, int64_t &result) {
    return a < b;
}

bool greater(const int64_t a, const int64_t b, int64_t &result) {
    return a > b;
}

bool equal(const int64_t a, const int64_t b, int64_t &result) {
    return a == b;
}


bool div_all(int64_t a, const int64_t b, int64_t &result) {
    if (b == 1) return a;

    while (a % b == 0) {
        a /= b;
    }

    return a;
}

bool shift_left(const int64_t a, const int64_t b, int64_t &result) {
    return b >= 0 ? a * (1 << b) : a / (1 << -b);
}

bool shift_right(const int64_t a, const int64_t b, int64_t &result) {
    return shift_left(a, -b);
}

bool parity_sign(const int64_t a, int64_t &result) {
    return a % 2 ? -1 : 1;
}

bool two_power(const int64_t a, int64_t &result) {
    return pow_floor(2, a);
}

bool nth_fib(int64_t a, int64_t &result) {
    if (a == -1) return 0;
    if (a < -1) return (a % 2 ? -1 : 1) * nth_fib(-2 - a);

    int64_t m = 1;
    int64_t n = 1;
    for (; a > 0; a--) { m = n - m; n += m; }

    return n;
}

bool nth_prime(int64_t a, int64_t &result) {
    if (a < 0) return -nth_prime(-1 - a);

    if (a < static_cast<int64_t>(N_PRIMES_10K)) {
        return PRIMES_10K[a];
    }

    int64_t val = PRIME_10K;
    for (; a > static_cast<int64_t>(N_PRIMES_10K); a--) {
        val = next_prime(val + 2);
    }

    return val;
}

bool ten_power(const int64_t a, int64_t &result) {
    return pow_floor(10, a);
}

bool is_even(const int64_t a, int64_t &result) {
    return a % 2 ? 0 : 1;
}

// TODO: signaling for different errors in factorial

bool gcd(const int64_t a, const int64_t b, int64_t &result) {
    return std::gcd(a, b);
}

bool lcm(const int64_t a, const int64_t b, int64_t &result) {
    return std::lcm(a, b);
}

bool int_nth_root(const int64_t a, const int64_t b, int64_t &result) {
    return std::pow(a, 1 / static_cast<long double>(b));
}

bool is_prime(int64_t a, int64_t &result) {
    if (a < 0) a = -a;

    for (const int64_t p : PRIMES_10K) {
        if (a == p) {
            return true;
        }

        if (a % p == 0) {
            return false;
        }

        if (p > a / p) {
            return true;
        }
    }

    for (uint32_t d = PRIME_10K; d <= a / d; d += 2) {
        if (a % d == 0) {
            return false;
        }
    }
    return true;
}

bool int_sqrt(const int64_t a, int64_t &result) {
    return std::sqrt(a);
}

bool set_interior(int64_t a, int64_t &result) {
    for (int64_t b = 1; b < a; b *= 2) {
        a |= b;
    }
    return a;
}

bool coprime(const int64_t a, const int64_t b, int64_t &result) {
    return gcd(a, b) == 1;
}

bool abs_diff(const int64_t a, const int64_t b, int64_t &result) {
    return std::abs(a - b);
}

bool get_bit(const int64_t a, const int64_t b, int64_t &result) {
    return (a >> b) & 1;
}

bool unset_bit(const int64_t a, const int64_t b, int64_t &result) {
    return a & ~(1 << b);
}

bool set_bit(const int64_t a, const int64_t b, int64_t &result) {
    return a | (1 << b);
}

bool toggle_bit(const int64_t a, const int64_t b, int64_t &result) {
    return a ^ (1 << b);
}

bool multiplicity(int64_t a, const int64_t b, int64_t &result) {
    // TODO: actually signal this
    if (b == 1) return -1;

    uint8_t k = 0;
    while (a % b == 0) {
      a /= b;
      k += 1;
    }

    return k;
}

bool sign(const int64_t a, int64_t &result) {
    if (a == 0) return 0;
    return a > 0 ? 1 : -1;
}

bool popcount(const int64_t a, int64_t &result) {
    // Note: GCC extension
    return __builtin_popcount(a);
}

bool floor_log_2(const int64_t a, int64_t &result) {
    return std::log2(a);
}

bool floor_log_10(const int64_t a, int64_t &result) {
    return std::log10(a);
}

bool between(const int64_t a, const int64_t b, const int64_t c, int64_t &result) {
    return b <= a && a < c;
}

bool clamp(const int64_t a, const int64_t b, const int64_t c, int64_t &result) {
    return std::min(std::max(a, b), c);
}

bool low_bit(const int64_t a, int64_t &result) {
    return a & -a;
}

bool high_bit(const int64_t a, int64_t &result) {
    return 1 << floor_log_2(a);
}

bool next_multiple(const int64_t a, const int64_t b, int64_t &result) {
    return std::ceil(static_cast<long double>(a) / b) * b;
}

bool is_power(const int64_t a, const int64_t b, int64_t &result) {
    return a == static_cast<int64_t>(std::pow(int_nth_root(a, b), b));
}

bool next_prime(int64_t a, int64_t &result) {
    while (!is_prime(a)) a++;
    return a;
}

bool last_prime(int64_t a, int64_t &result) {
    a--;
    while (!is_prime(a)) a--;
    return a;
}

bool totient(int64_t a, int64_t &result) {
    if (a < 0) a = -a;

    int64_t t = 1;
    uint8_t i = 0;

    while (a > 1) {
        if (const int64_t p = nth_prime(i); a % p == 0) {
            t *= p - 1;
            a /= p;

            while (a % p == 0) {
                t *= p;
                a /= p;
            }
        }
        i++;
    }

    return t;
}


#define STACK state->stack
#define DEPTH state->depth

bool alter_stack(State *state) {
    if (DEPTH < 3) return false;

    const int64_t t = STACK[DEPTH - 3];
    STACK[DEPTH - 3] = STACK[DEPTH - 2];
    STACK[DEPTH - 2] = STACK[DEPTH];
    STACK[DEPTH - 1] = t;
    return true;
}

bool both_copy(State *state) {
    if (DEPTH < 2) return false;

    STACK[DEPTH] = STACK[DEPTH - 2];
    STACK[DEPTH + 1] = STACK[DEPTH - 1];
    DEPTH += 2;
    return true;
}

bool copy(State *state) {
    if (DEPTH < 1) return false;

    STACK[DEPTH] = STACK[DEPTH - 1];
    DEPTH += 1;
    return true;
}

bool discard(State *state) {
    if (DEPTH < 1) return false;

    DEPTH -= 1;
    return true;
}

bool next(State *state) {
    if (DEPTH < 2) return false;

    STACK[DEPTH] = STACK[DEPTH - 2];
    DEPTH += 1;
    return true;
}

bool under(State *state) {
    if (DEPTH < 2) return false;

    STACK[DEPTH] = STACK[DEPTH - 1];
    STACK[DEPTH - 1] = STACK[DEPTH - 2];
    DEPTH += 1;
    return true;
}

bool swap(State *state) {
    if (DEPTH < 2) return false;

    const int64_t t = STACK[DEPTH - 1];
    STACK[DEPTH - 1] = STACK[DEPTH - 2];
    STACK[DEPTH - 2] = t;
    return true;
}

bool push(State *state, const int64_t val) {
    STACK[DEPTH] = val;
    DEPTH += 1;
    return true;
}

bool tuck(State *state, const int64_t val) {
    if (DEPTH < 1) return false;

    STACK[DEPTH] = STACK[DEPTH - 1];
    STACK[DEPTH - 1] = val;
    DEPTH += 1;
    return true;
}

bool unary(State *state, UnaryOp op) {
    if (DEPTH < 1) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 1], &result)) return false;

    STACK[DEPTH - 1] = result;
    return true;
}

bool binary(State *state, BinaryOp op) {
    if (DEPTH < 2) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 1], STACK[DEPTH - 2], &result)) return false;

    STACK[DEPTH - 2] = result;
    DEPTH -= 1;
    return true;
}

bool ternary(State *state, TernaryOp op) {
    if (DEPTH < 3) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 1], STACK[DEPTH - 2], STACK[DEPTH - 3], &result)) return false;

    STACK[DEPTH - 3] = result;
    DEPTH -= 2;
    return true;
}

bool X(State* state) {
    if (DEPTH < 1) return false;

    state->x = STACK[DEPTH - 1];
    state->x_init = true;
    return true;
}

bool Y(State* state) {
    if (DEPTH < 1) return false;

    state->y = STACK[DEPTH - 1];
    state->y_init = true;
    return true;
}

bool x(State* state) {
    if (!state->x_init) return false;

    push(state, state->x);
    return true;
}

bool y(State* state) {
    if (!state->y_init) return false;

    push(state, state->y);
    return true;
}


bool divmod(State *state) {
    if (DEPTH < 2) return false;

    STACK[DEPTH + 1] = mod(STACK[DEPTH], STACK[DEPTH - 1]);
    STACK[DEPTH + 2] = div_floor(STACK[DEPTH], STACK[DEPTH - 1]);
    DEPTH += 2;
    return true;
}

bool square_two(State *state) {
    if (DEPTH < 2) return false;

    STACK[DEPTH] = square(STACK[DEPTH]);
    STACK[DEPTH - 1] = square(STACK[DEPTH - 1]);
    return true;
}

#undef STACK
#undef DEPTH
