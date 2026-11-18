#include "du_math.h"
#include <math.h>

double duAbs(double x)                  { return fabs(x); }
double duMod(double x, double y)         { return fmod(x, y); }
double duSin(double x)                  { return sin(x); }
double duCos(double x)                  { return cos(x); }
double duTan(double x)                  { return tan(x); }
double duCot(double x)                  { return 1.0 / tan(x); }
double duLn(double x)                   { return log(x); }
double duLog(double x, double base)      { return log(x) / log(base); }
double duExp(double x)                  { return exp(x); }
double duPow(double base, double exp)    { return pow(base, exp); }
double duSqrt(double x)                 { return sqrt(x); }

double duPowI(double base, int32_t exponent)
{
    uint32_t power = exponent < 0 ? (uint32_t)(-(exponent + 1)) + 1U : (uint32_t)exponent;
    double result = 1.0;
    while (power != 0U) {
        if ((power & 1U) != 0U) result *= base;
        power >>= 1;
        if (power != 0U) base *= base;
    }
    return exponent < 0 ? 1.0 / result : result;
}
