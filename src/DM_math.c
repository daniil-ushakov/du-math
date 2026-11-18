#include "DM_math.h"
#include <math.h>

#define DM_LN2 0.69314718055994530941723212145817657

/* Return the remainder with the same sign as x. */
double dmMod(double x, double y)
{
    return fmod(x, y);
}

double dmAbs(double x)
{
    return x < 0.0 ? -x : x;
}

/* Taylor series after reducing the argument to [-pi/2, pi/2]. */
double dmSin(double x)
{
    double term, sum;
    int k;
    if (!isfinite(x)) return NAN;
    x = remainder(x, 2.0 * DM_PI);
    if (x > DM_PI / 2.0) x = DM_PI - x;
    if (x < -DM_PI / 2.0) x = -DM_PI - x;
    term = sum = x;
    for (k = 1; k <= 20; ++k) {
        term *= -x * x / ((2.0 * k) * (2.0 * k + 1.0));
        sum += term;
        if (dmAbs(term) < 1e-17) break;
    }
    return sum;
}

double dmCos(double x)
{
    double term = 1.0, sum = 1.0, sign = 1.0;
    int k;
    if (!isfinite(x)) return NAN;
    x = remainder(x, 2.0 * DM_PI);
    if (x > DM_PI / 2.0) { x = DM_PI - x; sign = -1.0; }
    if (x < -DM_PI / 2.0) { x = -DM_PI - x; sign = -1.0; }
    for (k = 1; k <= 20; ++k) {
        term *= -x * x / ((2.0 * k - 1.0) * (2.0 * k));
        sum += term;
        if (dmAbs(term) < 1e-17) break;
    }
    return sign * sum;
}

/* atanh-series for ln(m), where x=m*2^exponent and m is near 1. */
double dmLn(double x)
{
    int exponent, k;
    double m, z, z2, term, sum = 0.0;
    if (isnan(x) || x < 0.0) return NAN;
    if (x == 0.0) return -INFINITY;
    if (isinf(x)) return INFINITY;
    m = frexp(x, &exponent);
    if (m < 0.70710678118654752440) { m *= 2.0; --exponent; }
    z = (m - 1.0) / (m + 1.0);
    z2 = z * z;
    term = z;
    for (k = 1; k <= 31; k += 2) {
        sum += term / k;
        term *= z2;
    }
    return 2.0 * sum + exponent * DM_LN2;
}

double dmExp(double x)
{
    int k, i;
    double r, term = 1.0, sum = 1.0;
    if (isnan(x)) return NAN;
    if (x > 709.78271289338397) return INFINITY;
    if (x < -745.1332191019411) return 0.0;
    k = (int)floor(x / DM_LN2 + 0.5);
    r = x - k * DM_LN2;
    for (i = 1; i <= 32; ++i) {
        term *= r / i;
        sum += term;
        if (dmAbs(term) < 1e-17) break;
    }
    return ldexp(sum, k);
}

double dmPow(double base, double exponent)
{
    double result;
    if (isnan(base) || isnan(exponent)) return NAN;
    if (exponent == 0.0 || base == 1.0) return 1.0;
    if (base == 0.0) return exponent > 0.0 ? 0.0 : INFINITY;
    if (base < 0.0) {
        if (!isfinite(exponent) || exponent != trunc(exponent)) return NAN;
        result = dmExp(exponent * dmLn(-base));
        return fmod(dmAbs(exponent), 2.0) == 1.0 ? -result : result;
    }
    return dmExp(exponent * dmLn(base));
}

double dmSqrt(double x)
{
    double guess, next;
    int exponent, i;
    if (isnan(x) || x < 0.0) return NAN;
    if (x == 0.0 || isinf(x)) return x;
    frexp(x, &exponent);
    guess = ldexp(1.0, exponent / 2);
    for (i = 0; i < 32; ++i) {
        next = 0.5 * (guess + x / guess);
        if (next == guess) break;
        guess = next;
    }
    return guess;
}

double dmLog(double x, double base)
{
    if (base <= 0.0 || base == 1.0) return NAN;
    return dmLn(x) / dmLn(base);
}

double dmTan(double x)
{
    return dmSin(x) / dmCos(x);
}

double dmCot(double x)
{
    return dmCos(x) / dmSin(x);
}
