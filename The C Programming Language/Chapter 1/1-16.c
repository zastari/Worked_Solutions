/* KR 1-15: Revise the main routine of the longest-line program so it will
 * correctly print the length of arbitrarily long input lines, and as much
 * as possible of the text
 *
 * Notes: Changed getline from text to getaline due to conflict with getline
 *        from the standard library
 */
#include <stdio.h>

#define MAXLINE 20    /* Limit includes appended \0 */

int getaline(char s[], int lim);
void copy(char to[], char from[]);


int getaline(char s[], int lim) {
    int c, i;

    for(i = 0; (i < lim-1) && ((c = getchar()) != EOF) && (c != '\n'); ++i) {
        s[i] = c;
    }
    if(c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}


void copy(char to[], char from[]) {
    int i;
    for(i = 0; (to[i] = from[i]) != '\0'; ++i);
}


int main()
{
    int len, curlen, accumulate, max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = accumulate = curlen = 0;
    while((curlen = getaline(line, MAXLINE)) > 0) {      /* Calling getchar() once it returns EOF always returns EOF */
        if(accumulate == 1)
            len += curlen;
        else
            len = curlen;

        if(line[curlen-1] == '\n')
            accumulate = 0;
        else
            accumulate = 1;

        /* Always produce a MAXLINE size output if the longest line is longer than MAXLINE */
        if( ((len > max) && (len > MAXLINE) && accumulate == 1) || ((len > max) && (len < MAXLINE)) ) {
            copy(longest, line);
            max = len;
        }
    }

    if(max > 0) {
        printf("Longest line length: %d\n", max);
        printf("%s\n", longest);
    }
    else {
        printf("No lines were found.\n");
    }

    return 0;
}
