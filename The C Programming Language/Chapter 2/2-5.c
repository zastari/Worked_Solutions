/* KR 2-5: Write the function any(s1,s2), which returns the first location
 * in the string s1 where any character from the string s2 occurs, or -1 if s1
 * contains no characters from s2. (The standard library function strpbrk does
 * the same job but returns a pointer to the location.)
 */

#include <stdio.h>

int any(const char s1[], const char s2[]);
int strmatch(char c, const char s2[]);


int strmatch(char c, const char s2[])
{
    int i = 0;
    while(s2[i] != '\0') {
        if(c == s2[i])
            return i;
        i++;
    }

    return -1;
}


int any(const char s1[], const char s2[])
{
    int i;
    for(i = 0; s1[i] != '\0'; i++) {
        if(strmatch(s1[i], s2) != -1)
            return i;
    }

    return -1;
}


int main()
{
    const char s1[] = "The quick brown fox jumps over the lazy dog.";
    const char s2[] = "aeiou.";
    int index;

    index = any(s1,s2);

    printf("Match at index: %d\n", index);
    printf("Character match: %c\n", s1[index]);

    return 0;
}
