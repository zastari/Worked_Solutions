/* KR 5-3: Write a pointer version of the function strcat that we showed in
 *  Chapter 2: strcat(s,t) copies the string t to the end of s.
 */
#include <stdio.h>
#define MAXSIZE 1000

void mystrcat(char *s, char *t);


void mystrcat(char *s, char *t)
{
    while(*s++);
    s--;
    while(*s++ = *t++);
}


int main(void)
{
    char s[MAXSIZE] = "foo";
    char *t = "bar";
    mystrcat(s, t);
    printf("%s\n", s);
    return 0;
}
