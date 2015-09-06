/* KR 2-10: Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 */

#include <stdio.h>
char lower(char c);

char lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main()
{
    char c = 'F';
    printf("%c\n", lower(c));
    return 0;
}
