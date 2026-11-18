#include "du_math.h"
#include <math.h>

/* Standard C math functions are used for accuracy and target-specific optimizations. */
float duAbsF(float x)                 { return fabsf(x); }
float duModF(float x, float y)        { return fmodf(x, y); }
float duSinF(float x)                 { return sinf(x); }
float duCosF(float x)                 { return cosf(x); }
float duTanF(float x)                 { return tanf(x); }
float duCotF(float x)                 { return 1.0f / tanf(x); }
float duLnF(float x)                  { return logf(x); }
float duLogF(float x, float base)     { return logf(x) / logf(base); }
float duExpF(float x)                 { return expf(x); }
float duPowF(float base, float exp)   { return powf(base, exp); }
float duSqrtF(float x)                { return sqrtf(x); }

/* Exponentiation by squaring avoids the general-purpose powf for integer powers. */
float duPowIF(float base, int32_t exponent)
{
    uint32_t power = exponent < 0 ? (uint32_t)(-(exponent + 1)) + 1U : (uint32_t)exponent;
    float result = 1.0f;
    while (power != 0U) {
        if ((power & 1U) != 0U) result *= base;
        power >>= 1;
        if (power != 0U) base *= base;
    }
    return exponent < 0 ? 1.0f / result : result;
}

/* Fast polynomial approximations valid only on [-pi, pi]; no trigonometric libm calls. */
float duFastSinF(float x)
{
    float x2;
    if (x > 0.5f * DU_PI_F) x = DU_PI_F - x;
    else if (x < -0.5f * DU_PI_F) x = -DU_PI_F - x;
    x2 = x * x;
    return x * (1.0f + x2 * (-0.16666666666666666f +
           x2 * (0.00833333333333333f +
           x2 * (-0.00019841269841269f +
           x2 * (0.00000275573192239f +
           x2 * (-0.00000002505210838f))))));
}

float duFastCosF(float x)
{
    float x2, sign = 1.0f;
    if (x > 0.5f * DU_PI_F) { x = DU_PI_F - x; sign = -1.0f; }
    else if (x < -0.5f * DU_PI_F) { x = -DU_PI_F - x; sign = -1.0f; }
    x2 = x * x;
    return sign * (1.0f + x2 * (-0.5f +
           x2 * (0.04166666666666666f +
           x2 * (-0.00138888888888888f +
           x2 * (0.00002480158730158f +
           x2 * (-0.00000027557319223f))))));
}
