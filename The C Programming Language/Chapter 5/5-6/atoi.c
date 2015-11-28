/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 10
int atoi(char *s)
{
    int num = 0, sign = 1;
    if(*s == '-') {
        sign = -1;
        s++;
    }
    else if(*s == '+') {
        s++;
    }

    while(*s != '\0') {
        num = num * 10 + *s++ - '0';
    }
    return num * sign;
}
