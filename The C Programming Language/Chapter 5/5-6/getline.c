/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#define MAXSIZE 1000
void mygetline(char *s, int lim)
{
    int i = 0, c;
    while((c = getchar()) != EOF && c != '\n' && i++ < lim-1) {
        *s++ = c;
    }
    if(c != EOF) {
        *s++ = c;
    }
    *s = '\0';
}
