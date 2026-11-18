#include "du_math.h"
#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

static int near_f32(float a, float b, float eps)
{
    return fabsf(a - b) <= eps * (1.0f + fabsf(b));
}
static int near_f64(double a, double b, double eps)
{
    return fabs(a - b) <= eps * (1.0 + fabs(b));
}

int main(void)
{
    int i;
    float max_sin_err = 0.0f, max_cos_err = 0.0f;
    for (i = -100000; i <= 100000; ++i) {
        float x = DU_PI_F * (float)i / 100000.0f;
        float es = fabsf(duFastSinF(x) - sinf(x));
        float ec = fabsf(duFastCosF(x) - cosf(x));
        if (es > max_sin_err) max_sin_err = es;
        if (ec > max_cos_err) max_cos_err = ec;
    }
    assert(max_sin_err <= 1e-5f);
    assert(max_cos_err <= 1e-5f);
    for (i = -1000; i <= 1000; ++i) {
        float x = (float)i / 7.0f;
        assert(near_f32(duSinF(x), sinf(x), 1e-7f));
        assert(near_f32(duCosF(x), cosf(x), 1e-7f));
        assert(near_f32(duExpF(x / 100.0f), expf(x / 100.0f), 1e-7f));
    }
    for (i = 1; i < 1000; ++i) {
        float x = (float)i / 31.0f;
        assert(near_f32(duLnF(x), logf(x), 1e-7f));
        assert(near_f32(duSqrtF(x), sqrtf(x), 1e-7f));
    }
    assert(near_f32(duPowIF(-2.0f, 9), -512.0f, 1e-6f));
    assert(near_f32(duPowIF(2.0f, -4), 0.0625f, 1e-6f));
    assert(duPowIF(2.0f, 0) == 1.0f);
    assert(near_f64(duPowI(-2.0, 5), -32.0, 1e-12));
    assert(near_f64(duSin(DU_PI / 6.0), 0.5, 1e-12));
    assert(duSqrtF(0.0f) == 0.0f);
    assert(isnan(duSqrtF(-1.0f)));
    assert(duModF(-5.0f, 2.0f) == -1.0f);
    printf("math tests passed, fast sin err %.8g, cos err %.8g\n", max_sin_err, max_cos_err);
    return 0;
}
