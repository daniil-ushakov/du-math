#ifndef DU_MATH_H
#define DU_MATH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DU_PI   3.14159265358979323846264338327950288
#define DU_E    2.71828182845904523536028747135266250
#define DU_PI_F 3.14159265358979323846f
#define DU_E_F  2.71828182845904523536f

/* Single precision: recommended for microcontrollers with a single-precision FPU. */
float duAbsF(float x);
float duModF(float x, float y);
float duSinF(float x);
float duCosF(float x);
float duTanF(float x);
float duCotF(float x);
float duLnF(float x);
float duLogF(float x, float base);
float duExpF(float x);
float duPowF(float base, float exponent);
float duSqrtF(float x);
float duPowIF(float base, int32_t exponent);

/* Fast approximations: argument MUST be within [-DU_PI_F, DU_PI_F]. */
/* No reduction or libm calls; absolute error target <= 1e-5. */
float duFastSinF(float x);
float duFastCosF(float x);

/* Double precision: compile du_math_f64.c only when needed. */
double duAbs(double x);
double duMod(double x, double y);
double duSin(double x);
double duCos(double x);
double duTan(double x);
double duCot(double x);
double duLn(double x);
double duLog(double x, double base);
double duExp(double x);
double duPow(double base, double exponent);
double duSqrt(double x);
double duPowI(double base, int32_t exponent);

#ifdef __cplusplus
}
#endif

#endif
