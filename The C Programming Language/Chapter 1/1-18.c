/* KR 1-18: Write a program to delete trailing blanks and tabs from each line
 * of input, and to delete entirely blank lines
 *
 * Does not properly handle line's longer than MAXLINE length
 * A general solution that does not use pointers may be possible
 * using recursion on getaline
 */
#include <stdio.h>

#define MAXLINE 1000    /* Limit includes appended \0 */

int getaline(char s[], int lim);
void wtrim(char s[], int i);


int getaline(char s[], int lim) {
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if(c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}


void wtrim(char s[], int i) {
    int c;

    if(i > 0 && s[i-1] != '\n')
        return;    /* Exit if no whitespace to trim */

    s[--i] = '\0';
    --i;           /* Move prior to terminal \n */

    while(i>=0 && ((c=s[i])=='\t' || c==' ')) {
        s[i] = '\0';
        --i;
    }
    if(i > -1)
        s[i+1] = '\n';
}

int main()
{
    int len;
    char line[MAXLINE];

    while((len = getaline(line, MAXLINE)) > 0) {      /* Calling getchar() once it returns EOF always returns EOF */
        wtrim(line, len);
        printf("%s", line);
    }

    return 0;
}
