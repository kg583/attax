#include <cmath>
#include <numeric>
#include <stdlib.h>
#include "ops.h"
#include "primes.h"


bool add(const int64_t a, const int64_t b, int64_t &result) {
    result = a + b;
    return true;
}

bool sub(const int64_t a, const int64_t b, int64_t &result) {
    result = a - b;
    return true;
}

bool mul(const int64_t a, const int64_t b, int64_t &result) {
    result = a * b;
    return true;
}

bool div_floor(const int64_t a, const int64_t b, int64_t &result) {
    // Infinity
    if (b == 0) return false;

    result = (a + (a < 0)) / b - (a < 0);
    return true;
}

bool mod(const int64_t a, const int64_t b, int64_t &result) {
    if (b == 0) return false;

    result = a % b;
    return true;
}

bool pow_floor(const int64_t a, const int64_t b, int64_t &result) {
    return pow_mod(a, b, 0, result);
}

bool inc(const int64_t a, int64_t &result) {
    result = a + 1;
    return true;
}

bool dec(const int64_t a, int64_t &result) {
    result = a - 1;
    return true;
}

bool halve(const int64_t a, int64_t &result) {
    result = a / 2;
    return true;
}

bool unhalve(const int64_t a, int64_t &result) {
    result = a * 2;
    return true;
}

bool bit_and(const int64_t a, const int64_t b, int64_t &result) {
    result = a & b;
    return true;
}

bool bit_or(const int64_t a, const int64_t b, int64_t &result) {
    result = a | b;
    return true;
}

bool bit_xor(const int64_t a, const int64_t b, int64_t &result) {
    result = a ^ b;
    return true;
}

bool square(const int64_t a, int64_t &result) {
    result = a * a;
    return true;
}

bool negate(const int64_t a, int64_t &result) {
    result = -a;
    return true;
}

bool abs_value(const int64_t a, int64_t &result) {
    result = std::abs(a);
    return true;
}

bool min(const int64_t a, const int64_t b, int64_t &result) {
    result = std::min(a, b);
    return true;
}

bool max(const int64_t a, const int64_t b, int64_t &result) {
    result = std::max(a, b);
    return true;
}


bool logical_not(const int64_t a, int64_t &result) {
    result = !a;
    return true;
}

bool less(const int64_t a, const int64_t b, int64_t &result) {
    result = a < b;
    return true;
}

bool greater(const int64_t a, const int64_t b, int64_t &result) {
    result = a > b;
    return true;
}

bool equal(const int64_t a, const int64_t b, int64_t &result) {
    result = a == b;
    return true;
}


bool div_all(int64_t a, int64_t b, int64_t &result) {
    b = std::abs(b);

    if (a == 0 || b == 0 || b == 1) {
        result = a;
        return true;
    };

    while (a % b == 0) {
        a /= b;
    }

    result = a;
    return true;
}

bool shift_left(const int64_t a, const int64_t b, int64_t &result) {
    result = b >= 0 ? a * (1 << b) : a / (1 << -b);
    return true;
}

bool shift_right(const int64_t a, const int64_t b, int64_t &result) {
    result = b <= 0 ? a * (1 << b) : a / (1 << -b);
    return true;
}

bool parity_sign(const int64_t a, int64_t &result) {
    result = a % 2 ? -1 : 1;
    return true;
}

bool two_power(const int64_t a, int64_t &result) {
    return pow_floor(2, a, result);
}

bool nth_fib(const int64_t a, int64_t &result) {
    return nth_fib_mod(a, 0, result);
}

bool nth_prime(int64_t a, int64_t &result) {
    if (a < 0) {
        if (!nth_prime(-1 - a, result)) return false;
        result = -result;
        return true;
    }

    if (a < static_cast<int64_t>(N_PRIMES_10K)) {
        result = PRIMES_10K[a];
        return true;
    }

    if (a > 300000) return false;

    result = PRIME_10K;
    for (; a > static_cast<int64_t>(N_PRIMES_10K); a--) {
        next_prime(result + 2, result);
    }
    return true;
}

bool ten_power(const int64_t a, int64_t &result) {
    return pow_floor(10, a, result);
}

bool is_even(const int64_t a, int64_t &result) {
    result = a % 2 ? 0 : 1;
    return true;
}

bool factorial(const int64_t a, int64_t& result) {
    if (a < 0 || a > 20) return false;

    result = 1;
    for (int64_t k = 2; k <= a; k++) result *= k;

    return true;
}

bool gcd(const int64_t a, const int64_t b, int64_t &result) {
    result = std::gcd(a, b);
    return true;
}

bool lcm(const int64_t a, const int64_t b, int64_t &result) {
    result = std::lcm(a, b);
    return true;
}

bool int_nth_root(const int64_t a, const int64_t b, int64_t &result) {
    if (b == 0) return false;
    result = std::pow(a, 1 / static_cast<long double>(b));
    return true;
}

bool is_prime(int64_t a, int64_t &result) {
    if (a < 0) a = -a;

    for (const int64_t p : PRIMES_10K) {
        if (a == p) {
            result = true;
            return true;
        }

        if (a % p == 0) {
            result = false;
            return true;
        }

        if (p > a / p) {
            result = true;
            return true;
        }
    }

    for (uint32_t d = PRIME_10K; d <= a / d; d += 2) {
        if (a % d == 0) {
            result = false;
            return true;
        }
    }
    result = true;
    return true;
}

bool int_sqrt(const int64_t a, int64_t &result) {
    result = std::sqrt(a);
    return true;
}

bool set_interior(const int64_t a, int64_t &result) {
    result = a;
    for (int64_t b = 1; b < a; b *= 2) {
        result |= b;
    }
    return true;
}

bool coprime(const int64_t a, const int64_t b, int64_t &result) {
    result = std::gcd(a, b) == 1;
    return true;
}

bool abs_diff(const int64_t a, const int64_t b, int64_t &result) {
    result = std::abs(a - b);
    return true;
}

bool get_bit(const int64_t a, const int64_t b, int64_t &result) {
    result = (a >> b) & 1;
    return true;
}

bool unset_bit(const int64_t a, const int64_t b, int64_t &result) {
    result = a & ~(1 << b);
    return true;
}

bool set_bit(const int64_t a, const int64_t b, int64_t &result) {
    result = a | (1 << b);
    return true;
}

bool toggle_bit(const int64_t a, const int64_t b, int64_t &result) {
    result = a ^ (1 << b);
    return true;
}

bool multiplicity(int64_t a, const int64_t b, int64_t &result) {
    // Timeout in interpreter
    if (b == 1) {
        return false;
    };

    result = 0;
    while (a % b == 0) {
      a /= b;
      result += 1;
    }
    return true;
}

bool sign(const int64_t a, int64_t &result) {
    result = a == 0 ? 0 : (a > 0 ? 1 : -1);
    return true;
}

bool popcount(const int64_t a, int64_t &result) {
    // Note: GCC extension
    result = __builtin_popcount(a);
    return true;
}

bool floor_log_2(const int64_t a, int64_t &result) {
    result = std::log2(a);
    return true;
}

bool floor_log_10(const int64_t a, int64_t &result) {
    result = std::log10(a);
    return true;
}

bool between(const int64_t a, const int64_t b, const int64_t c, int64_t &result) {
    result = b <= a && a < c;
    return true;
}

bool clamp(const int64_t a, const int64_t b, const int64_t c, int64_t &result) {
    result = std::min(std::max(a, b), c);
    return true;
}

bool low_bit(const int64_t a, int64_t &result) {
    result = a & -a;
    return true;
}

bool high_bit(const int64_t a, int64_t &result) {
    int64_t log;
    floor_log_2(a, log);
    result = 1 << log;
    return true;
}

bool next_multiple(const int64_t a, const int64_t b, int64_t &result) {
    if (b == 0) return false;

    result = std::ceil(static_cast<long double>(a) / b) * b; 
    return true;
}

bool is_power(const int64_t a, const int64_t b, int64_t &result) {
    int64_t second_result;
    if (!int_nth_root(a, b, second_result)) return false;

    result = a == static_cast<int64_t>(std::pow(second_result, b));
    return true;
}

bool next_prime(int64_t a, int64_t &result) {
    while (true) {
        int64_t prime;
        is_prime(a, prime);

        if (prime) {
            result = a;
            return true;
        }
        a++;
    }
}

bool last_prime(int64_t a, int64_t &result) {
    while (true) {
        int64_t prime;
        is_prime(a, prime);

        if (prime) {
            result = a;
            return true;
        }
        a--;
    }
}

bool totient(int64_t a, int64_t &result) {
    if (a < 0) a = -a;

    int64_t t = 1;
    uint8_t i = 0;

    while (a > 1) {
        int64_t p;
        nth_prime(i, p);

        if (a % p == 0) {
            t *= p - 1;
            a /= p;

            while (a % p == 0) {
                t *= p;
                a /= p;
            }
        }
        i++;
    }

    result = t;
    return true;
}


bool pow_mod(int64_t a, int64_t b, const int64_t m, int64_t &result) {
    if (a == 0) {
        if (b < 0) return false;
        if (b == 0) result = m != 1 && m != -1;
        if (b > 0) result = 0;

    } else {
        if (b < 0) {
            result = 0;
        } else {
            if (int64_t check; !int_nth_root(INT64_MAX, b, check) || (m == 0 && a > check)) return false;

            result = 1;
            while (b) {
                if (b & 1) {
                    result *= a;
                    if (m != 0) result %= m;
                }

                b >>= 1;
                a *= a;
            }
        }
    }

    return true;
}

bool nth_fib_mod(int64_t a, const int64_t m, int64_t &result) {
    if (a == -1) {
        result = 0;
        return true;
    }

    if (a < -1) {
        if (!nth_fib(-2 - a, result)) return false;

        result *= a % 2 ? -1 : 1;
        if (m != 0) result %= m;
        return true;
    }

    if (m == 0 && a > 25) return false;

    int64_t n = 1;
    result = 1;
    for (; a > 0; a--) {
        n = result - n;
        result += n;

        if (m != 0) {
            n %= m;
            result %= m;
        }
    }

    return true;
}

bool factorial_mod(const int64_t a, const int64_t m, int64_t& result) {
    if (a < 0 || (m == 0 && a > 20)) return false;

    result = 1;
    for (int64_t k = 2; k <= a; k++) {
        result *= k;
        if (m != 0) result %= m;
    }

    return true;
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

bool unary(State *state, bool (*op)(int64_t, int64_t &result)) {
    if (DEPTH < 1) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 1], result)) return false;

    STACK[DEPTH - 1] = result;
    return true;
}

bool binary(State *state, bool (*op)(int64_t, int64_t, int64_t &result)) {
    if (DEPTH < 2) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 2], STACK[DEPTH - 1], result)) return false;

    STACK[DEPTH - 2] = result;
    DEPTH -= 1;
    return true;
}

bool ternary(State *state, bool (*op)(int64_t, int64_t, int64_t, int64_t &result)) {
    if (DEPTH < 3) return false;

    int64_t result;
    if (!op(STACK[DEPTH - 3], STACK[DEPTH - 2], STACK[DEPTH - 1], result)) return false;

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

    const int64_t dividend = STACK[DEPTH - 2];
    const int64_t divisor = STACK[DEPTH - 1];
    int64_t quotient;
    int64_t remainder;

    if (!div_floor(dividend, divisor, quotient)) return false;
    if (!mod(dividend, divisor, remainder)) return false;

    STACK[DEPTH - 2] = quotient;
    STACK[DEPTH - 1] = remainder;
    return true;
}

bool square_two(State *state) {
    if (DEPTH < 2) return false;

    int64_t lower;
    int64_t upper;

    if (!square(STACK[DEPTH - 2], lower)) return false;
    if (!square(STACK[DEPTH - 1], upper)) return false;

    STACK[DEPTH - 2] = lower;
    STACK[DEPTH - 1] = upper;
    return true;
}

#undef STACK
#undef DEPTH
