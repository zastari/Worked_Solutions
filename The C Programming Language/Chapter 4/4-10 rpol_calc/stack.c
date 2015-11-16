#include <stdio.h>
#include <math.h>
#include "calc.h"

#define STACKSIZE 100

double val[STACKSIZE];
int sp = 0;


void push(double f)
{
    if(sp < STACKSIZE) {
        val[sp++] = f;
    } else {
        printf("Error: Stack full, can't push %g\n", f);
    }
}


double pop(void)
{
    if(sp > 0) {
        return val[--sp];
    } else {
        return NAN;
    }
}


void clear(void)
{
    sp = 0;
}
