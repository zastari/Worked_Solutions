/* KR 2-3: Write a function htoi(s), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
 * through 9, a through f, and A through F
 */

#include <stdio.h>
#include <ctype.h>

unsigned int htoi(const char s[]);

unsigned int htoi(const char s[])
{
    unsigned int i, n;
    i = n = 0;

    if(s[0] == '0' && tolower(s[1]) == 'x')     /* Trim 0x or 0X from hex input */
        i = 2;

    while(1) {
        if(s[i] >= '0' && s[i] <= '9')
            n = n * 16 + (s[i] - '0');
        else if (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'f')
            n = n * 16 + (10 + tolower(s[i]) - 'a');
        else
            break;
        ++i;
    }

    return n;
}

int main()
{
    char s[] = "0Xd3aDB33f";
    printf("%s = %u\n", s, htoi(s));

    return 0;
}
