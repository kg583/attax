#include <cmath>
#include <numeric>
#include <stdlib.h>
#include "ops.h"
#include "primes.h"


int64_t add(const int64_t a, const int64_t b) {
    return a + b;
}

int64_t sub(const int64_t a, const int64_t b) {
    return a - b;
}

int64_t mul(const int64_t a, const int64_t b) {
    return a * b;
}

int64_t div_floor(const int64_t a, const int64_t b) {
    return (a + (a < 0)) / b - (a < 0);
}

int64_t mod(const int64_t a, const int64_t b) {
    return a % b;
}

int64_t pow_floor(const int64_t a, const int64_t b) {
    return std::pow(a, b);
}

int64_t inc(const int64_t a) {
    return a + 1;
}

int64_t dec(const int64_t a) {
    return a - 1;
}

int64_t halve(const int64_t a) {
    return a / 2;
}

int64_t unhalve(const int64_t a) {
    return a * 2;
}

int64_t bit_and(const int64_t a, const int64_t b) {
    return a & b;
}

int64_t bit_or(const int64_t a, const int64_t b) {
    return a | b;
}

int64_t bit_xor(const int64_t a, const int64_t b) {
    return a ^ b;
}

int64_t square(const int64_t a) {
    return a * a;
}

int64_t negate(const int64_t a) {
    return -a;
}

int64_t min(const int64_t a, const int64_t b) {
    return std::min(a, b);
}

int64_t max(const int64_t a, const int64_t b) {
    return std::max(a, b);
}


int64_t logical_not(const int64_t a) {
    return !a;
}

int64_t less(const int64_t a, const int64_t b) {
    return a < b;
}

int64_t greater(const int64_t a, const int64_t b) {
    return a > b;
}

int64_t equal(const int64_t a, const int64_t b) {
    return a == b;
}


int64_t div_all(int64_t a, const int64_t b) {
    if (b == 1) return a;

    while (a % b == 0) {
        a /= b;
    }

    return a;
}

int64_t shift_left(const int64_t a, const int64_t b) {
    return b >= 0 ? a * (1 << b) : a / (1 << -b);
}

int64_t shift_right(const int64_t a, const int64_t b) {
    return shift_left(a, -b);
}

int64_t parity_sign(const int64_t a) {
    return a % 2 ? -1 : 1;
}

int64_t two_power(const int64_t a) {
    return pow_floor(2, a);
}

// TODO: set up precomputation of Fibonacci numbers

int64_t nth_prime(int64_t a) {
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

int64_t ten_power(const int64_t a) {
    return pow_floor(10, a);
}

int64_t is_even(const int64_t a) {
    return a % 2 ? 0 : 1;
}

// TODO: signaling for different errors in factorial

int64_t gcd(const int64_t a, const int64_t b) {
    return std::gcd(a, b);
}

int64_t lcm(const int64_t a, const int64_t b) {
    return std::lcm(a, b);
}

int64_t is_prime(int64_t a) {
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

int64_t int_sqrt(const int64_t a) {
    return std::sqrt(a);
}

int64_t set_interior(int64_t a) {
    for (int64_t b = 1; b < a; b *= 2) {
        a |= b;
    }
    return a;
}

int64_t coprime(const int64_t a, const int64_t b) {
    return gcd(a, b) == 1;
}

int64_t abs_diff(const int64_t a, const int64_t b) {
    return std::abs(a - b);
}

int64_t get_bit(const int64_t a, const int64_t b) {
    return (a >> b) & 1;
}

int64_t unset_bit(const int64_t a, const int64_t b) {
    return a & ~(1 << b);
}

int64_t set_bit(const int64_t a, const int64_t b) {
    return a | (1 << b);
}

int64_t toggle_bit(const int64_t a, const int64_t b) {
    return a ^ (1 << b);
}

int64_t multiplicity(int64_t a, const int64_t b) {
    // TODO: actually signal this
    if (b == 1) return -1;

    uint8_t k = 0;
    while (a % b == 0) {
      a /= b;
      k += 1;
    }

    return k;
}

int64_t sign(const int64_t a) {
    if (a == 0) return 0;
    return a > 0 ? 1 : -1;
}

int64_t floor_log_2(const int64_t a) {
    return std::log2(a);
}

int64_t floor_log_10(const int64_t a) {
    return std::log10(a);
}

int64_t between(const int64_t a, const int64_t b, const int64_t c) {
    return b <= a && a < c;
}

int64_t clamp(const int64_t a, const int64_t b, const int64_t c) {
    return std::min(std::max(a, b), c);
}

int64_t low_bit(const int64_t a) {
    return a & -a;
}

int64_t high_bit(const int64_t a) {
    return 1 << floor_log_2(a);
}

int64_t next_multiple(const int64_t a, const int64_t b) {
    return std::ceil(static_cast<long double>(a) / b) * b;
}

int64_t next_prime(int64_t a) {
    while (!is_prime(a)) a++;
    return a;
}

int64_t last_prime(int64_t a) {
    a--;
    while (!is_prime(a)) a--;
    return a;
}

int64_t totient(int64_t a) {
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

bool unary(State *state, int64_t (*op)(int64_t)) {
    if (DEPTH < 1) return false;

    STACK[DEPTH - 1] = op(STACK[DEPTH - 1]);
    return true;
}

bool binary(State *state, int64_t (*op)(int64_t, int64_t)) {
    if (DEPTH < 2) return false;

    STACK[DEPTH - 2] = op(STACK[DEPTH - 1], STACK[DEPTH - 2]);
    DEPTH -= 1;
    return true;
}

bool ternary(State *state, int64_t (*op)(int64_t, int64_t, int64_t)) {
    if (DEPTH < 3) return false;

    STACK[DEPTH - 3] = op(STACK[DEPTH - 1], STACK[DEPTH - 2], STACK[DEPTH - 3]);
    DEPTH -= 2;
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
