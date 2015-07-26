// KR 1-15: Rewrite the temperature conversion program of Section 1.2 to use a function for conversion
#include <stdio.h>

float fahr_to_celsius(int);

float fahr_to_celsius(int fahr)
{
    return (5 * (fahr - 32)) / 9.0;
}

int main()
{
    int lower, upper, step, i;
    lower = 0;
    upper = 300;
    step = 20;

    for(i = lower; i <= upper; i += step) {
        printf("%3d: %6.1f\n", i, fahr_to_celsius(i));
    }

    return 0;
}

