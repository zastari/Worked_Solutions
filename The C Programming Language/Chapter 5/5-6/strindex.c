/* KR 5-6: Rewrite appropriate programs from earlier chapters and exercises
 *   with pointers instead of array indexing. Good possibilities include
 *   getline, atoi, itoa, reverse, strrindex, and getop.
 */
#include <stdio.h>
#include <string.h>
#include "5-6.h"
#define MAXSIZE 100
int strrindex(char *s, char *t)
{
    int maxindex = -1;
    for(int i = 0; *(s+i) != '\0'; i++) {
        int j;
        for(j = 0; *(s+i+j) == *(t+j) && *(t+j) != '\0'; j++);
        if(*(t+j) == '\0') {
            maxindex = i;
        }
    }

    return maxindex;
}
