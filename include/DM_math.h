#ifndef DM_MATH_H
#define DM_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#define DM_PI 3.14159265358979323846264338327950288
#define DM_E  2.71828182845904523536028747135266250

double dmAbs(double x);
double dmMod(double x, double y);
double dmSin(double x);
double dmCos(double x);
double dmTan(double x);
double dmCot(double x);
double dmLn(double x);
double dmLog(double x, double base);
double dmExp(double x);
double dmPow(double base, double exponent);
double dmSqrt(double x);

#ifdef __cplusplus
}
#endif

#endif
