/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strrindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 100
int main(void)
{
    char s[MAXSIZE] = "foobar";
    char t[MAXSIZE] = "bar";
    printf("%d\n", strrindex(s,t));

    strncpy(s, "baz", MAXSIZE);
    strncpy(t, "bay", MAXSIZE);
    printf("%d\n", strrindex(s,t));

    strncpy(s, "foobar", MAXSIZE);
    strncpy(t, "bart", MAXSIZE);
    printf("%d\n", strrindex(s,t));

    strncpy(s, "foobarfoobar", MAXSIZE);
    strncpy(t, "foo", MAXSIZE);
    printf("%d\n", strrindex(s,t));

    return 0;
}
