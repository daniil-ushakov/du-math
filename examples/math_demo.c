#include "DM_math.h"
#include <stdio.h>

int main(void)
{
    printf("sin(pi/6) = %.12f\n", dmSin(DM_PI / 6.0));
    printf("ln(2)     = %.12f\n", dmLn(2.0));
    printf("sqrt(2)   = %.12f\n", dmSqrt(2.0));
    return 0;
}
