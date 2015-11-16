#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP 100

int main()
{
    int type;
    double op, op2;
    char s[MAXOP];
    int vars[26];

    char *line = NULL;
    size_t size;

    while(getline(&line, &size, stdin) != -1) {
        while((type = getop(line, s)) != '\n') {
            switch(type) {
                case NUMBER:
                    push(atof(s));
                    break;
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
                        printf("error: division by zero\n");
                    }
                    break;
                /* KR 4-6: Add commands for handling variables */
                case '=':
                    vars[s[0]-'A'] = pop();
                    break;
                case VAR_GET:
                    push(vars[s[0]-'A']);
                    break;
                /* KR 4-3: Add modulus */
                case '%':
                    op = pop();
                    push(fmod(pop(), op));
                    break;
                /* KR 4-5: Add math library functions sin, exp, pow */
                case SIN:
                    push(sin(pop()));
                    break;
                case EXP:
                    push(exp(pop()));
                    break;
                case POW:
                    op = pop();
                    push(pow(pop(), op));
                    break;
                /* KR 4-4: Add peek, clear, swap */
                case PEEK:
                    op2 = pop();
                    printf("Top of stack: %.8g\n", op2);
                    push(op2);
                    break;
                case REPLACE:
                    op2 = pop();
                    op = pop();
                    push(op2);
                    push(op);
                    break;
                case CLEAR:
                    clear();
                    break;
                default:
                    printf("Unknown command %s\n", s);
                    break;
            }
        }
        printf("\t%.8g\n", pop());
    }

    return 0;
}
