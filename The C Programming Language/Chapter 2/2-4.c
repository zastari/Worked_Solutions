/* KR 2-4: Write an alternate version of squeeze(s1,s2) that deletes
 * each character in s1 that matches any character in the string s2
 */

#include <stdio.h>

void squeezestr(char s1[], const char s2[]);
int strmatch(char c, const char s2[]);


int strmatch(char c, const char s2[])
{
    int i = 0;
    while(s2[i] != '\0') {
        if(c == s2[i])
            return 1;
        i++;
    }

    return 0;
}


void squeezestr(char s1[], const char s2[])
{
    int i, j;
    for(i = j = 0; s1[i] != '\0'; ++i) {
        if(!strmatch(s1[i], s2)) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}


int main()
{
    char s1[] = "The quick brown fox jumps over the lazy dog.";
    const char s2[] = "aeiou.";

    squeezestr(s1,s2);

    printf("%s\n", s1);

    return 0;
}
