/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 100
int main()
{
    char s[MAXSIZE];
    itoa(s, 123456789, MAXSIZE-1);
    printf("%s\n", s);

    itoa(s, -15, MAXSIZE-1);
    printf("%s\n", s);
    return 0;
}
