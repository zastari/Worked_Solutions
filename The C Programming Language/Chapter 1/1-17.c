// KR 1-17: Write a program to print all input lines that are longer than 80 characters
#include <stdio.h>

#define PRINTLINE 81    /* Print lines 81 characters or longer */

int getaline(char s[], int lim);

int getaline(char s[], int lim) {
    int c, i;

    for(i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
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
    char line[PRINTLINE+1];     /* Include space for terminal \0 */

    accumulate = 0;
    while((len = getaline(line, PRINTLINE+1)) > 0) {      /* Calling getchar() once it returns EOF always returns EOF */
        if( (accumulate == 1) || ((accumulate == 0) && (len > PRINTLINE)) )
            printf("%s", line);

        if(line[len-1] == '\n')
            accumulate = 0;
        else {
            accumulate = 1;
        }
    }

    return 0;
}
