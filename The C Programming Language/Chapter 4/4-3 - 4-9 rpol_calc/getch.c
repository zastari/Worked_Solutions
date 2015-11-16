#include <stdio.h>
#include "calc.h"

#define BUFSIZE 100

/* KR 4-9: Modify getch and ungetch to handle a push-back EOF
   (change char buf to int buf) */

int buf = '\0';

/* KR 4-8: Assume that there will never be more than 1 character of pushback
   and modify getch / ungetch accordingly */
int getch(void)
{
    int bufchar;
    if(buf != '\0') {
        bufchar = buf;
        buf = '\0';
        return bufchar;
    }
    return getchar();
}

void ungetch(int c)
{
    if(buf != '\0') {
        printf("Can't ungetch(), char %d already  in buffer\n", buf);
    } else {
        buf = c;
    }
}

/* KR 4-7: Write a routine that will push back an entire string onto
   the input */
void ungets(char s[])
{
    for(int i = 0; s[i] != '\0'; i++) {
        ungetch(s[i]);
    }
}
