/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 10
int main(void)
{
    printf("%d %d %d %d\n", atoi("387"), atoi("-228761"), atoi("+20074"), atoi("+deadbeef"));
    return 0;
}
