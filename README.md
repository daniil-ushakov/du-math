# DU Math

Математическая библиотека на C99 для микроконтроллеров и ПК. Поддерживает C++ через extern "C". Не использует динамическую память.

## Использование на микроконтроллере

- Только float: добавьте include/du_math.h и src/du_math_f32.c.
- Поддержка double: отдельно добавьте src/du_math_f64.c.
- Функции duSinF, duCosF, duLnF и аналогичные вызывают стандартные функции C (sinf, cosf, logf и т. п.). Их скорость и размер прошивки определяются реализацией libm и компилятором; они не обязательно быстрее libm.
- duFastSinF и duFastCosF не вызывают libm и используют полиномиальные приближения. **Аргумент обязательно должен лежать в интервале [-π, π].** Целевая максимальная абсолютная ошибка — 1e-5 на этом интервале. Для произвольных аргументов используйте duSinF/duCosF или предварительное приведение угла.
- duPowIF и duPowI вычисляют целочисленные степени методом двоичного возведения.

## Пример C99

~~~c
#include "du_math.h"

float a = duSinF(DU_PI_F / 6.0f);
float b = duFastSinF(DU_PI_F / 6.0f);
float c = duPowIF(2.0f, 10);
~~~

## API

Float: duAbsF, duModF, duSinF, duCosF, duTanF, duCotF, duLnF, duLogF, duExpF, duPowF, duSqrtF, duPowIF, duFastSinF, duFastCosF.

Double: duAbs, duMod, duSin, duCos, duTan, duCot, duLn, duLog, duExp, duPow, duSqrt, duPowI.

## Проверка без CMake

~~~sh
gcc -std=c99 -O2 -Wall -Wextra -Werror -Iinclude src/du_math_f32.c src/du_math_f64.c tests/test_math.c -lm -o test_math
./test_math
~~~

В IAR или Keil подключайте нужные исходники вручную. Измеряйте время выполнения и код на своей целевой платформе; преимуществ по скорости над оптимизированной libm и CMSIS-DSP не заявляется. Не включайте -ffast-math без оценки погрешности.
