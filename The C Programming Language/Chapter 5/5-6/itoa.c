/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 100
void itoa(char *s, int num, int lim)
{
    int sign = 1;
    char *t = s;

    if(num < 0) {
        sign = -1;
        num *= -1;
    }
    for(int i = 0; num && i < lim; i++) {
        *t++ = num % 10 + '0';
        num /= 10;
    }
    if(sign == -1) {
        *t++ = '-';
    }
    *t = '\0';

    reverse(s);
}
