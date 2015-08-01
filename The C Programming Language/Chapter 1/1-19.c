/* KR 1-18: Reverse a string
 *
 * Does not handle lines longer than MAXLINE in length
 */
#include <stdio.h>

#define MAXLINE 1000       /* Limit includes appended \0 */

int getaline(char s[], int lim);
void reverse(char s[], char r[], int i);

int getaline(char s[], int lim)
{
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;

    if(c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}


void reverse(char s[], char r[], int i)
{
    int j = 0;

    r[i] = '\0';
    r[i-1] = '\n';         /* Truncate lines > MAXLINE in length */
    i -= 2;
    while(i >= 0) {
        r[i] = s[j];
        i--;
        j++;
    }
}


int main()
{
    int len;
    char line[MAXLINE];
    char rev[MAXLINE];

    while((len = getaline(line, MAXLINE)) > 0) {      /* Calling getchar() once it returns EOF always returns EOF */
        reverse(line, rev, len);
        printf("%s", rev);
    }

    return 0;
}
