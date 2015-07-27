// KR 1-17: Write a program to print all input lines that are longer than 80 characters

#include <stdio.h>

#define PRINTLINE 80
#define MAXLINE 1000    /* Limit includes appended \0 */

int getaline(char s[], int lim);

int getaline(char s[], int lim) {
    int c, i;

    for(i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}


int main()
{
    int len, accumulate;
    char line[MAXLINE];

    accumulate = 0;
    while((len = getaline(line, MAXLINE)) > 0) {      /* Calling getchar() once it returns EOF always returns EOF */
        if((accumulate == 0) && (len > PRINTLINE+1))
            printf("%s", line);

        if(line[len-1] == '\n')
            accumulate = 0;
        else {
            if(accumulate == 0)
                putchar('\n');
            accumulate = 1;
        }
    }

    return 0;
}
