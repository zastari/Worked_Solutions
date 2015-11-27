/* KR 4-14: Define a macro swap(t,x,y) that swaps two varibles of type t
     Note: var names like a_b, c and a, b_c will cause collisions if
     they have the same type. */
#include <stdio.h>
#define swap(t,x,y) t x ## _ ## y; x ## _ ## y = x; x = y; y = x ## _ ## y

int main()
{
    int x = 3, y =4;
    char a = 'a', b = 'b';
    char c = 'c', d = 'd';
    swap(int, x, y);
    printf("%d %d\n", x, y);
    swap(char, a, b);
    printf("%c %c\n", a, b);
    swap(char, c, d);
    printf("%c %c\n", c ,d);
    return 0;
}
