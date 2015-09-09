/* KR 3-6: Write a version of itoa that accepts three arguments instead of
 * two. The third argument is a minimum field width; the converted number must
 * be padded with blanks on the left if necessary to make it wide enough.
 */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int w);
void reverse(char s[]);

/* Reverse string in place by swapping values that are equidistant from the midpoint */
void reverse(char s[])
{
    const int len = strlen(s);
    int i;
    char temp;
    for(i = 0; i < len/2; i++) {
        temp = s[i];
        s[i] = s[(len-1)-i];
        s[(len-1)-i] = temp;
    }
}

void itoa(int n, char s[], int w) {
    int i, sign;

    sign = (n >= 0) ? 1 : -1;
    i = 0;
    do {
        s[i++] = (n%10) >= 0 ? (n%10)+'0' : -(n%10)+'0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';

    while(i < w) {
        s[i++] = ' ';
    }

    s[i] = '\0';
    reverse(s);
}


int main()
{
    int n = -2147483648;
    char s[20];     /* Hold any int +1 character to make bounds checking easier */
    itoa(n, s, 18);
    printf("%s\n", s);
    return 0;
}
