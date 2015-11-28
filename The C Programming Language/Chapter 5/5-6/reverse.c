/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 1000
void reverse(char *s)
{
    char *i = s;
    char tmp;

    while(*(i+1)) {
        i++;
    }

    while(s < i) {
        tmp = *i;
        *i = *s;
        *s = tmp;
        s++, i--;
    }
}
