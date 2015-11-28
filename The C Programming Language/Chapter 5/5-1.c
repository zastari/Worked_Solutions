#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);
int getint(int *);


static int buf = '\0';

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


int getint(int *pn)
{
    int c, sign;

    while(isspace(c = getch()));

    if(c != '+' && c != '-' && c != EOF && !isdigit(c)) {
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if(c == '-' || c == '+') {
        c = getch();
        if(!isdigit(c)) {
            ungetch(c);
            return 0;
        }
    }

    for(*pn = 0; isdigit(c); c = getch()) {
        *pn = *pn * 10 + c - '0';
    }
    *pn *= sign;

    if(c != EOF) {
        ungetch(c);
    }

    return c;
}


int main()
{
    int n = 0, array[SIZE];
    int c;

    while(n < SIZE && (c = getint(&array[n])) != EOF) {
        if(c != 0) {
            n++;
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
