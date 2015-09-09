/* KR 3-4: Write the function itob(n,s,b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n,s,16) formats n as a hexadecimal integer in s.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int n, char s[], int b);
void reverse(char s[]);
char charmap(int c);

char charmap(int c)
{
    if(c < 0)
        c = -c;

    if(c >= 0 && c <= 9) {
        return c + '0';
    }
    else if (c >= 10 && c <= 15) {
        return c - 10 + 'a';
    }
    return 0;
}


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


void itob(int n, char s[], int b) {
    int i, sign;

    if(b < 2 || b > 16) {
        printf("Base out of accepted range 2 - 16. Base was: %u\n", b);
        exit(1);
    }

    sign = (n >= 0) ? 1 : -1;
    i = 0;
    do {
        s[i++] = charmap(n%b);
    } while ((n /= b) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main()
{
    int test_numbers[] = {-1, 1, -2147483648, -2147483648, 2147483647, 2147483647, 123, 123, 1234, 1234, -123, -123, 11259375};
    int test_bases[] = {2, 2, 10, 16, 10, 16, 10, 3, 10, 3, 10, 3, 16};

    int i;
    char s[33];     /* Hold any int +1 character to make bounds checking easier */
    for(i = 0; i < sizeof(test_numbers)/sizeof(int); ++i) {
        itob(test_numbers[i], s, test_bases[i]);
        printf("%db%d: %s\n", test_numbers[i], test_bases[i], s);
    }

    return 0;
}
