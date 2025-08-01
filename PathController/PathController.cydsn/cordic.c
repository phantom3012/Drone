#include "cordic.h"

#include <stdint.h>
#include <math.h>

typedef int32_t fixed_t;

#define DOUBLE_TO_FIXED(d) ((fixed_t)(d) * (1 << 16))
#define FIXED_TO_DOUBLE(f) ((double)(f) / (1 << 16))

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_PI_2
#define M_PI_2 (M_PI / 2.0)
#endif

#define CORDIC_ITERATIONS 16

static const fixed_t cordic_angle_table[CORDIC_ITERATIONS] = {
    51472, 30386, 16054, 8150, 4091, 2047, 1024, 512,
    256, 128, 64, 32, 16, 8, 4, 2};

#define CORDIC_K_INV 39734

static fixed_t cordic_atan2_core(fixed_t y, fixed_t x)
{
    fixed_t z_angle = 0;
    fixed_t x_new, y_new;
    int i, sign;

    if (x < 0)
    {
        if (y >= 0)
        {
            x_new = y;
            y_new = -x;
            z_angle = DOUBLE_TO_FIXED(M_PI_2);
        }
        else
        {
            x_new = -y;
            y_new = x;
            z_angle = -DOUBLE_TO_FIXED(M_PI_2);
        }
        x = x_new;
        y = y_new;
    }

    for (i = 0; i < CORDIC_ITERATIONS; ++i)
    {
        sign = (y < 0) ? -1 : 1;
        x_new = x + (sign * (y >> i));
        y_new = y - (sign * (x >> i));
        z_angle -= sign * cordic_angle_table[i];
        x = x_new;
        y = y_new;
    }
    return z_angle;
}

static void cordic_sincos_core(fixed_t angle, fixed_t *s, fixed_t *c)
{
    fixed_t x, y, z;
    fixed_t x_new, y_new;
    int i, sign;

    x = CORDIC_K_INV;
    y = 0;
    z = angle;

    for (i = 0; i < CORDIC_ITERATIONS; ++i)
    {
        sign = (z < 0) ? -1 : 1;
        x_new = x - (sign * (y >> i));
        y_new = y + (sign * (x >> i));
        z -= sign * cordic_angle_table[i];
        x = x_new;
        y = y_new;
    }
    *c = x;
    *s = y;
}

double fast_atan2(double y, double x)
{
    fixed_t y_fixed = DOUBLE_TO_FIXED(y);
    fixed_t x_fixed = DOUBLE_TO_FIXED(x);
    fixed_t angle_fixed = cordic_atan2_core(y_fixed, x_fixed);
    return FIXED_TO_DOUBLE(angle_fixed);
}

void fast_sincos(double angle, double *s, double *c)
{
    angle = fmod(angle + M_PI, 2.0 * M_PI) - M_PI;
    fixed_t angle_fixed = DOUBLE_TO_FIXED(angle);
    fixed_t s_fixed, c_fixed;
    cordic_sincos_core(angle_fixed, &s_fixed, &c_fixed);
    *s = FIXED_TO_DOUBLE(s_fixed);
    *c = FIXED_TO_DOUBLE(c_fixed);
}