#include "5-7.h"
#include "../5-6/5-6.h"
#include <string.h>
#include <stdio.h>
int readlines2(char **lineptr, char *lines, int maxlines)
{
    int len, nlines;

    nlines = 0;
    while((len = mygetline(lines, MAXLEN)) > 0) {
        if(nlines >= maxlines) {
            return -1;
        } else {
            *(lines+len-1) = '\0';
            *(lineptr+nlines++) = lines;
            lines += len;
        }
    }

    return nlines;
}


void writelines(char **lineptr, int nlines)
{
    while(nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}
