/* KR 5-10: Write the program expr, which evaluates a reverse Polish expression
 *   from the command line, where each operator or operand is a separate
 *   argument.
 */
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define STACKSIZE 100

double val[STACKSIZE];
double *sp = val;

void push(double f)
{
    if(sp - val <= STACKSIZE-1) {
        *sp++ = f;
    } else {
        printf("Error: Stack full, can't push %g\n", f);
    }
}


double pop()
{
    if(sp > val) {
        return *--sp;
    } else {
        return NAN;
    }
}


int main(int argc, char **argv)
{
    char *s;
    double op;
    argv++;     /* Skip basename */

    while(--argc > 0) {
        s = *argv++;
        if(strlen(s) == 1 && !isdigit(*s)) {
            switch(*s) {
                case '+':
                    push(pop() + pop());
                    break;
                case '-':
                    op = pop();
                    push(pop() - op);
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '/':
                    op = pop();
                    if(op != 0.0) {
                        push(pop() / op);
                    } else {
                        printf("Error: Division by zero\n");
                    }
                    break;
            }
        } else {
            push(atof(s));
        }
    }
    printf("%g\n", pop());
    return 0;
}
