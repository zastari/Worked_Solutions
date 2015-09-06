/* KR 2-8; Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n bit positions.
 */
#include <stdio.h>

unsigned rightrot(unsigned x, unsigned n);


unsigned rightrot(unsigned x, unsigned n)
{
    unsigned len = 8*(unsigned)sizeof(unsigned);  /* Get number of total bits for rotation */
    return (x >> n) | (x << (len-n));
}


int main()
{
    unsigned x = 255;
    unsigned n = 6;

    printf("%u\n", rightrot(x,n));

    return 0;
}

