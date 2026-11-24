#ifndef EXEC_H
#define EXEC_H

#include "ops.h"


inline void execute(State *state, const Op op) {
    if (op.is_number) {
        push(state, op.opcode);
        return;
    }

    switch (op.opcode) {

    case 0x23: binary(state, pow_floor); return;
    case 0x25: binary(state, mod); return;
    case 0x2A: binary(state, mul); return;
    case 0x2B: binary(state, add); return;
    case 0x2D: binary(state, sub); return;
    case 0x2F: binary(state, div_floor); return;
    case 0x4A: unary(state, square); return;
    case 0x48: unary(state, unhalve); return;
    case 0x49: binary(state, bit_and); return;
    case 0x4D: binary(state, bit_or); return;
    case 0x4E: unary(state, negate); return;
    case 0x53: binary(state, bit_xor); return;
    case 0x54: binary(state, max); return;
    case 0x5E: unary(state, inc); return;
    case 0x68: unary(state, halve); return;
    case 0x74: binary(state, min); return;
    case 0x76: unary(state, dec); return;

    case 0x21: unary(state, not); return;
    case 0x3C: binary(state, less); return;
    case 0x3D: binary(state, equal); return;
    case 0x3E: binary(state, greater); return;

    case 0x5B: under(state); return;
    case 0x61: alter_stack(state); return;
    case 0x62: both_copy(state); return;
    case 0x63: copy(state); return;
    case 0x64: discard(state); return;
    case 0x6E: next(state); return;
    case 0x73: swap(state); return;

    case 0x3A21: binary(state, coprime); return;
    case 0x3A2B: unary(state, sign); return;
    case 0x3A2D: binary(state, abs_diff); return;
    case 0x3A2F: binary(state, multiplicity); return;
    // case 0x3A31: unary(state, popcount); return;
    case 0x3A32: unary(state, floor_log_2); return;
    case 0x3A3A: binary(state, toggle_bit); return;
    case 0x3A40: binary(state, get_bit); return;
    case 0x3A41: unary(state, floor_log_10); return;
    case 0x3A47: unary(state, high_bit); return;
    case 0x3A4A: square_two(state); return;
    // case 0x3A4E: binary(state, is_power); return;
    // case 0x3A50: unary(state, next_prime); return;
    case 0x3A5B: binary(state, unset_bit); return;
    case 0x3A5D: binary(state, set_bit); return;
    case 0x3A62: ternary(state, between); return;
    case 0x3A63: ternary(state, clamp); return;
    case 0x3A67: unary(state, low_bit); return;
    case 0x3A6D: binary(state, next_multiple); return;
    // case 0x3A70: unary(state, last_prime); return;
    // case 0x3A74: unary(state, totient); return;
    case 0x3A7E: unary(state, set_interior); return;

    case 0x7C25: divmod(state); return;
    case 0x7C2F: binary(state, div_all); return;
    case 0x7C31: unary(state, parity_sign); return;
    case 0x7C32: unary(state, two_power); return;
    // case 0x7C35: unary(state, nth_fib); return;
    // case 0x7C36: unary(state, nth_prime); return;
    case 0x7C3C: binary(state, shift_left); return;
    case 0x7C3E: binary(state, shift_right); return;
    case 0x7C41: unary(state, ten_power); return;
    // case 0x7C43: binary(state, choose); return;
    // case 0x7C46: unary(state, factorial); return;
    // case 0x7C6E: binary(state, int_nth_root); return;
    case 0x7C61: unary(state, llabs); return;
    case 0x7C65: unary(state, is_even); return;
    case 0x7C67: binary(state, gcd); return;
    case 0x7C6C: binary(state, lcm); return;
    // case 0x7C70: unary(state, is_prime); return;
    case 0x7C71: unary(state, int_sqrt); return;

    default:
    }
}


#endif
