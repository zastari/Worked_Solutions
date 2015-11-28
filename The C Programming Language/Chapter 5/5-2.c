/* KR 5-2: Write getfloat, the floating point version of getint. What type
 *   does getfloat return as its value?
 *
 *   Answer: int. The return type is only used to indicate what type of
 *   value was encountered:
 *     0: non-digit
 *   EOF: EOF
 *    ~0: digit
 */
#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int getch(void);
void ungetch(int);
int getfloat(float *);


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


int getfloat(float *pn)
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
    if(c == '.') {
        c = getch();
        for(float decimal = 10.0; isdigit(c); c = getch(), decimal *= 10.0) {
            *pn = *pn + (c - '0') / decimal;
        }
    }
    *pn *= sign;

    if(c != EOF) {
        ungetch(c);
    }

    return c;
}


int main()
{
    int n = 0;
    float array[SIZE];
    int c;

    while(n < SIZE && (c = getfloat(&array[n])) != EOF) {
        if(c != 0) {
            n++;
        }
    }

    for(int i = 0; i < n; i++) {
        printf("%f ", array[i]);
    }
    printf("\n");

    return 0;
}
