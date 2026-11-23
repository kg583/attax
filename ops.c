#include <math.h>
#include <stdint.h>
#include <stdlib.h>

// For expanding to floats and such later
typedef int64_t Num;


Num add(Num a, Num b) {
    return a + b;
}

Num sub(Num a, Num b) {
    return a - b;
}

Num mul(Num a, Num b) {
    return a * b;
}

// TODO: C and Stax round division differently

Num mod(Num a, Num b) {
    return a % b;
}

// TODO: integer pow

Num inc(Num a) {
    return a + 1;
}

Num dec(Num a) {
    return a - 1;
}

Num halve(Num a) {
    return a / 2;
}

Num unhalve(Num a) {
    return a * 2;
}

int64_t bit_and(int64_t a, int64_t b) {
    return a & b;
}

int64_t bit_or(int64_t a, int64_t b) {
    return a | b;
}

int64_t bit_xor(int64_t a, int64_t b) {
    return a ^ b;
}

Num square(Num a) {
    return a * a;
}

Num negate(Num a) {
    return -a;
}

int64_t min(int64_t a, int64_t b) {
    return a < b ? a : b;
}

int64_t max(int64_t a, int64_t b) {
    return a > b ? a : b;
}

int64_t div_all(int64_t a, int64_t b) {
    while (a % b == 0) {
        a /= b;
    }

    return a;
}

int64_t shift_left(int64_t a, int64_t b) {
    return b >= 0 ? a << b : a >> -b;
}

int64_t shift_right(int64_t a, int64_t b) {
    return shift_left(a, -b);
}

// TODO: set up precomputation of Fibonacci numbers and primes

int64_t parity_sign(int64_t a) {
    return a % 2 ? -1 : 1;
}

int64_t is_even(int64_t a) {
    return a % 2 ? 0 : 1;
}

// TODO: signaling for different errors in factorial

// TODO: support negative inputs
int64_t gcd(int64_t a, int64_t b) {
    if (a == 0) return b;
    if (b == 0) return a;

    return a >= b ? gcd(b, a % b) : gcd(b % a, a);
}

int64_t is_coprime(int64_t a, int64_t b) {
    return gcd(a, b) == 1 ? 1 : 0;
}

Num abs_diff(Num a, Num b) {
    return abs(a - b);
}

int64_t get_bit(int64_t a, int64_t b) {
    return (a >> b) & 1;
}

int64_t unset_bit(int64_t a, int64_t b) {
    return a & ~(1 << b);
}

int64_t set_bit(int64_t a, int64_t b) {
    return a | (1 << b);
}

int64_t multiplicity(int64_t a, int64_t b) {
    int k = 0;
    while (a % b == 0) {
      a /= b;
      k += 1;
    }

    return k;
}

int64_t sign(Num a) {
    if (a == 0) return 0;
    return a > 0 ? 1 : -1;
}

Num clamp(Num a, Num b, Num c) {
    return min(max(a, b), c);
}

int64_t low_bit(int64_t a) {
    return a & -a;
}
