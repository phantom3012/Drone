/**
 * @file cordic.c
 * @brief Fixed-point CORDIC implementation for fast atan2, sin, and cos.
 */
#include "cordic.h"
#include <stdint.h>
#include <math.h>

// --- Fixed-Point Math Definitions ---
// We use a 32-bit signed integer for Q16.16 fixed-point representation.
typedef int32_t fixed_t;
#define DOUBLE_TO_FIXED(d) ((fixed_t)((d) * (1 << 16)))
#define FIXED_TO_DOUBLE(f) ((double)(f) / (1 << 16))

// --- CORDIC Constants ---
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_PI_2
#define M_PI_2 (M_PI / 2.0)
#endif

// The number of CORDIC iterations determines the accuracy.
#define CORDIC_ITERATIONS 16

// Pre-computed table of atan(2^-i) values in Q16.16 fixed-point format.
// The original table was incorrect. This is the corrected version.
static const fixed_t cordic_angle_table[CORDIC_ITERATIONS] = {
    51472, 30386, 16054, 8150, 4091, 2047, 1024, 512,
    256,   128,   64,    32,   16,   8,    4,    2
};

// CORDIC gain factor K. For N iterations, K = product(sqrt(1 + 2^(-2i))).
// For sin/cos calculation, we need to divide by K. We use 1/K to do this
// with a multiplication. 1/K for 16 iterations is ~0.60725.
// In Q16.16 format, CORDIC_K_INV = 0.60725 * 2^16 = 39794.
#define CORDIC_K_INV 39794


// --- Core CORDIC Implementation (Static Functions) ---

/**
 * @brief Core CORDIC atan2 calculation in vectoring mode.
 */
static fixed_t cordic_atan2_core(fixed_t y, fixed_t x) {
    fixed_t z_angle = 0;
    fixed_t x_new, y_new;
    int i, sign;

    // Quadrant correction: rotate vector into the right half-plane.
    if (x < 0) {
        if (y >= 0) { // Q2
            x_new = y; y_new = -x; z_angle = DOUBLE_TO_FIXED(M_PI_2);
        } else { // Q3
            x_new = -y; y_new = x; z_angle = -DOUBLE_TO_FIXED(M_PI_2);
        }
        x = x_new; y = y_new;
    }

    // CORDIC vectoring mode loop.
    for (i = 0; i < CORDIC_ITERATIONS; ++i) {
        sign = (y < 0) ? -1 : 1;
        x_new = x + (sign * (y >> i));
        y_new = y - (sign * (x >> i));
        // The goal is to drive y to 0. If y is positive, we rotate
        // clockwise (subtract angle). If y is negative, rotate counter-clockwise.
        z_angle -= sign * cordic_angle_table[i];
        x = x_new; y = y_new;
    }
    return z_angle;
}

/**
 * @brief Core CORDIC sin/cos calculation in rotation mode.
 */
static void cordic_sincos_core(fixed_t angle, fixed_t *s, fixed_t *c) {
    fixed_t x, y, z;
    fixed_t x_new, y_new;
    int i, sign;

    // Initialize the vector (x, y) to (1/K, 0).
    // 1/K is the CORDIC gain, pre-multiplying by 1/K avoids a final division.
    x = CORDIC_K_INV;
    y = 0;
    z = angle;

    // CORDIC rotation mode loop.
    for (i = 0; i < CORDIC_ITERATIONS; ++i) {
        // Rotate to make the angle approach zero
        sign = (z < 0) ? -1 : 1;
        
        x_new = x - (sign * (y >> i));
        y_new = y + (sign * (x >> i));
        z -= sign * cordic_angle_table[i];
        
        x = x_new;
        y = y_new;
    }

    // After rotation, x = cos(angle) and y = sin(angle)
    *c = x;
    *s = y;
}


// --- Public API Implementation ---

double fast_atan2(double y, double x) {
    fixed_t y_fixed = DOUBLE_TO_FIXED(y);
    fixed_t x_fixed = DOUBLE_TO_FIXED(x);
    fixed_t angle_fixed = cordic_atan2_core(y_fixed, x_fixed);
    return FIXED_TO_DOUBLE(angle_fixed);
}

void fast_sincos(double angle, double *s, double *c) {

    angle = fmod(angle + M_PI, 2.0 * M_PI) - M_PI;

    fixed_t angle_fixed = DOUBLE_TO_FIXED(angle);
    fixed_t s_fixed, c_fixed;

    cordic_sincos_core(angle_fixed, &s_fixed, &c_fixed);

    *s = FIXED_TO_DOUBLE(s_fixed);
    *c = FIXED_TO_DOUBLE(c_fixed);
}
