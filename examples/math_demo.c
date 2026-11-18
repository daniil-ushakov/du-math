#include "du_math.h"
#include <stdio.h>

int main(void)
{
    float angle = DU_PI_F / 6.0f;
    printf("sin(pi/6): %.7f\n", duSinF(angle));
    printf("fast sin:  %.7f\n", duFastSinF(angle));
    printf("sqrt(2):   %.7f\n", duSqrtF(2.0f));
    printf("(-2)^9:    %.1f\n", duPowIF(-2.0f, 9));
    return 0;
}
