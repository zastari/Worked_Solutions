/* KR 2-6: Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the other
 * bits unchanged
 *
 * Solution Strategy:
 *      0 out the bits of x from p to p+1-n with an & mask
 *      OR those bits with the n rightmost bits from y
 */

#include <stdio.h>
#include <math.h>

unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y);


unsigned setbits(unsigned x, unsigned p, unsigned n, unsigned y)
{
    unsigned shift = p+1-n;  /* Amount to bitshift masks based on size of n vs position p */
    unsigned mask_bits = (unsigned)powf(2,n)-1;
    unsigned xmask = mask_bits << shift;  /* 1 from n to n+p, 0 otherwise */
    unsigned ymask = mask_bits;
    return (x&~xmask) | (ymask & y) << shift;
}


int main()
{
    unsigned x, y;
    x = 170;    /* 10101010 */
    y = 12;     /* 00001100 */

    unsigned p, n;
    p = 5;
    n = 4;

    printf("%u\n", setbits(x, p, n, y));

    return 0;
}
