/* KR 4-1: Write the function strrindex(s,t), which returns the position
 * of the rightmost occurrence of t in s, or -1 if there is none
 */
#include <stdio.h>

int strrindex(char s[], char t[]);

int strrindex(char s[], char t[])
{
    int i, j;
    int index = -1;

    for(i = 0; s[i] != '\0'; i++) {
        for(j = 0; s[i+j]==t[j] && t[j]!='\0'; j++)
        ;
        if(t[j] == '\0') {
            index = i;
        }
    }

    return index;
}

int main()
{
    char s[] = "strstrstr";
    char t[] = "str";
    printf("%d\n", strrindex(s, t));

    return 0;
}
