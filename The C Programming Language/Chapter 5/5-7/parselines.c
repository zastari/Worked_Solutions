#include "5-7.h"
#include "alloc.h"
#include "../5-6/5-6.h"
#include <string.h>
#include <stdio.h>
int readlines(char **lineptr, int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while((len = mygetline(line, MAXLEN)) > 0) {
        if(nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* Change \n to \0 */
            strcpy(p, line);
            *(lineptr+nlines++) = p;
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
