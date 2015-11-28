/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 1000
int main(void)
{
    char s[MAXSIZE] = "abcdefghijklmnopqrstuvwxyz";
    reverse(s);
    printf("%s\n", s);

    strncpy(s, "123456 789 0 ", MAXSIZE);
    reverse(s);
    printf("%s\n", s);
    return 0;
}
