/* KR 3-4: In a tow's complement number representation, our version of
 * itoa does not handle the largest negative number, that is, the value of n equal
 * to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 *
 * Explanation: int has range -x to x-1 where x = 2^31 on modern systems.
 * Generally, -(-y) = y, but since x > x-1, -(-x) overflows, yielding -(-x) = -x
 * on a two's complement system.
 */
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

/* Reverse string in place by swapping values that are equidistant from the midpoint */
void reverse(char s[])
{
    const int len = strlen(s) - 1;      /* Omit terminal \0 from length */
    int i;
    char temp;
    for(i = 0; i < len/2; i++) {
        temp = s[i];
        s[i] = s[len-i];
        s[len-i] = temp;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    sign = (n >= 0) ? 1 : -1;
    do {
        s[i++] = (n%10) >= 0 ? (n%10)+'0' : -(n%10)+'0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main()
{
    int n = -2147483648;
    char s[12];     /* Hold any int +1 character to make bounds checking easier */
    itoa(n, s);
    printf("%s\n", s);
    return 0;
}
