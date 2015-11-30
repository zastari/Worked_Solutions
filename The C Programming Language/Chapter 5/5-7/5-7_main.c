#include <stdio.h>
#include <string.h>
#include "5-7.h"
char lines[MAXLINES*MAXLEN];
char *lineptr[MAXLINES];

int main(void)
{
    int nlines;
    if ((nlines = readlines2(lineptr, lines, MAXLINES)) >= 0) {
        qsort_hoare(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: Input too big to sort\n");
        return 1;
    }
}
