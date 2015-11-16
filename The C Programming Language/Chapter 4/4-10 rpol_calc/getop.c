#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int linep = 0;
/* s[] will contain a float if NUMBER is returned
   otherwise it will contain the op returned */
int getop(char line[], char s[])
{
    int i = 0, pointcount = 0;
    while(line[linep] == ' ' || line[linep] == '\t') {
        linep++;
    }

    if(line[linep] == '\n') {
        linep = 0;
        return '\n';
    }

    while(!isspace(line[linep]) && line[linep] != '\0') {
        s[i++] = line[linep++];
    }

    s[i] = '\0';

    /* KR 4-6: Add support for 26 variables */
    if(s[0] >= 'A' && s[0] <= 'Z') {
        if(s[1] == '=') {
            return '=';
        } else {
            return VAR_GET;
        }
    }

    if(!isdigit(s[0]) && s[0] != '.' && s[0] != '-') {
        return s[0];
    }

    /* KR 4-3: Support negative numbers */
    if(s[0] == '-' && !isdigit(s[1])) {
            return s[0];
    }

    for(i = 1; s[i] != '\0'; i++) {
        if(s[i] == '.') {
            pointcount++;
            if(pointcount > 1) {
                return UNKNOWN;
            }
        }
        else if(!isdigit(s[i]) || (s[i] == '-' && i > 0)) {
            return UNKNOWN;
        }
    }

    return NUMBER;
}
