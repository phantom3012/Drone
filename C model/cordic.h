/**
 * @file cordic.h
 * @brief Public API for the fixed-point CORDIC math library.
 */
#ifndef CORDIC_H
#define CORDIC_H

/**
 * @brief Approximates atan2(y, x) using a fixed-point CORDIC algorithm.
 *
 * This function is the public interface to the CORDIC module. It provides a
 * fast, integer-based approximation of the four-quadrant arctangent function.
 *
 * @param y The y-coordinate (double).
 * @param x The x-coordinate (double).
 * @return A double approximating atan2(y, x) in radians.
 */
double fast_atan2(double y, double x);

/**
 * @brief Approximates sin(angle) and cos(angle) using a CORDIC algorithm.
 *
 * This function calculates both sine and cosine for a given angle in a single
 * operation, which is more efficient than separate calls.
 *
 * @param angle The input angle in radians (double).
 * @param s A pointer to a double where the sine result will be stored.
 * @param c A pointer to a double where the cosine result will be stored.
 */
void fast_sincos(double angle, double *s, double *c);


#endif // CORDIC_H
