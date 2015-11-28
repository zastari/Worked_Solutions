/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include "5-6.h"
#define MAXSIZE 1000
int main(void)
{
    char s[MAXSIZE];
    do {
        mygetline(s, MAXSIZE-1);
        printf("%s", s);
    } while (*s != '\0');

    return 0;
}
