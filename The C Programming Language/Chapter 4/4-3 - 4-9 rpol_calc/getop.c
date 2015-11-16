#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* s[] will contain a float if NUMBER is returned
   otherwise it will contain the op returned */
int getop(char s[])
{
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    /* KR 4-6: Add support for 26 variables */
    if(c >= 'A' && c <= 'Z') {
        c2 = getch();
        if(c2 == '=') {
            return c2;
        } else {
            ungetch(c2);
            return VAR_GET;
        }
    }

    if(!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    /* KR 4-3: Support negative numbers */
    if(c == '-') {
        c = getch();
        if(!isdigit(c)) {
            ungetch(c);
            return s[0];
        }
        ungetch(c);
    }

    i = 0;
    if(isdigit(c)) {
        while(isdigit(s[++i] = c = getch()))
            ;
    }
    if(c == '.') {
        while(isdigit(s[++i] = c = getch()))
            ;
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return NUMBER;
}
