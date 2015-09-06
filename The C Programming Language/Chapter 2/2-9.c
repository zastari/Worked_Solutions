/* KR 2-9: In a two's complement number system, x &= (x-1) deletes the 
 * rightmost 1-bit in x. Explain why. Use this observation to write a faster
 * version of bitcount.
 *
 * Reasoning: x-1 turns all bits to the right of the first 1 to 1. so x & (x-1)
 * will set these bits to 0. x-1 turns the first 1 to a 0, so this bit will be 0
 * as well.
 */
#include <stdio.h>

unsigned bitcount(unsigned x);

unsigned bitcount(unsigned x)
{
    int i;
    while(x != 0) {
        x &= x-1;
        i++;
    }

    return i;
}


int main()
{
    unsigned x = 170;
    printf("%u\n", bitcount(x));
    return 0;
}
