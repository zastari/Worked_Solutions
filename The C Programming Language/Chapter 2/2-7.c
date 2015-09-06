/* KR 2-7: Write a function invert(x,p,n) that returns x with the n
 * bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving
 * the others unchanged.
 */
#include <stdio.h>
#include <math.h>

unsigned invert(unsigned x, unsigned p, unsigned n);


unsigned invert(unsigned x, unsigned p, unsigned n)
{
    unsigned mask;
    mask = ((unsigned)powf(2,n)-1) << (p+1-n);
    return (x&~mask) | (~x&mask);
}


int main()
{
    unsigned x = 170; /* 10101010 */
    unsigned p = 5;
    unsigned n = 4;

    printf("%u\n", invert(x,p,n)); /* 10010110 = 150 */

    return 0;
}
