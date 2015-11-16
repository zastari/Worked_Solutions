#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* s[] will contain a double if NUMBER is returned
   otherwise it will contain the op returned */
int getop(char s[])
{
    int i, c, c2;
    static int cbuf = -2;

    while(1) {
        if(cbuf != -2) {
            c = cbuf;
            cbuf = -2;
        } else {
            c = getch();
        }

        if(c != ' ' && c != '\t') {
            break;
        }
    }

    s[0] = c;
    s[1] = '\0';

    /* KR 4-6: Add support for 26 variables */
    if(c >= 'A' && c <= 'Z') {
        c2 = getch();
        if(c2 == '=') {
            return c2;
        } else {
            cbuf = c2;
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
            cbuf = c;
            return s[0];
        }
        cbuf = c;
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
        cbuf = c;
    }

    return NUMBER;
}
