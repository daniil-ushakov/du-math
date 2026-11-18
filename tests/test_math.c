#include "DM_math.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

static int close_to(double a, double b, double tol)
{
    return fabs(a - b) <= tol * (1.0 + fabs(b));
}

int main(void)
{
    int i;
    for (i = -1000; i <= 1000; ++i) {
        double x = i / 10.0;
        assert(close_to(dmSin(x), sin(x), 1e-12));
        assert(close_to(dmCos(x), cos(x), 1e-12));
        assert(close_to(dmExp(x / 10.0), exp(x / 10.0), 1e-12));
    }
    for (i = 1; i <= 1000; ++i) {
        double x = i / 37.0;
        assert(close_to(dmLn(x), log(x), 1e-12));
        assert(close_to(dmSqrt(x), sqrt(x), 1e-12));
    }
    assert(close_to(dmPow(-2.0, 3.0), -8.0, 1e-12));
    assert(close_to(dmPow(2.0, -3.0), 0.125, 1e-12));
    assert(close_to(dmLog(8.0, 2.0), 3.0, 1e-12));
    assert(dmSqrt(0.0) == 0.0);
    assert(dmMod(-5.0, 2.0) == -1.0);
    assert(isnan(dmPow(-2.0, 0.5)));
    assert(isnan(dmSqrt(-1.0)));
    assert(isinf(dmLn(0.0)));
    puts("math tests passed");
    return 0;
}
