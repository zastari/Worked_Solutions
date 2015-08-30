/* KR 2-1: Write a program to determine the ranges of char, short, int
 * and long variables, both signed and unsinged, by printing appropriate
 * values from standard headers and by direct computation. Harder if you
 * compute them: determine the ranges of the various floating point types
 *
 * Note: Signed integer overflows are undefined behavior. This is only
 * guaranteed to work properly on a two's complement system
 */
#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

void int_limits();
void int_computed();
void float_limits();
void float_computed();

void int_limits()
{
    printf("%22d %22d signed char\n", SCHAR_MIN, SCHAR_MAX);
    printf("%22d %22d unsigned char\n", 0, UCHAR_MAX);
    printf("%22d %22d char\n", CHAR_MIN, CHAR_MAX);
    printf("%22d %22d signed short int\n", SHRT_MIN, SHRT_MAX);
    printf("%22d %22d unsigned short int\n", 0, USHRT_MAX);
    printf("%22d %22d signed int\n", INT_MIN, INT_MAX);
    printf("%22d %22u unsigned int\n", 0, UINT_MAX);
    printf("%22ld %22ld signed long\n", LONG_MIN, LONG_MAX);
    printf("%22d %22lu unsigned long\n", 0, ULONG_MAX);
}


void int_computed()
{
    signed char sc;
    unsigned char usc;
    char c;
    signed short int ssi;
    unsigned short int usi;
    signed int si;
    unsigned int ui;
    signed long sl;
    unsigned long ul;

    sc = usc = c = ssi = usi = si = ui = sl = ul = 2;
    while(sc > 0) {
        sc *= 2;
        if(sc <= 0)
            printf("%22d %22d signed char\n", sc, (signed char)(sc-1));
    }
    while(usc > 0) {
        usc *= 2;
        if(usc <= 0)
            printf("%22d %22d unsigned char\n", usc, (unsigned char)(usc-1));
    }
    while(c > 0) {
        c *= 2;
        if(c <= 0)
            printf("%22d %22d char\n", c, (char)(c-1));
    }
    while(ssi > 0) {
        ssi *= 2;
        if(ssi <= 0)
            printf("%22d %22d signed short int\n", ssi, (signed short int)(ssi-1));
    }
    while(usi > 0) {
        usi *= 2;
        if(usi <= 0)
            printf("%22d %22d unsigned short int\n", usi, (unsigned short int)(usi-1));
    }
    while(si > 0) {
        si *= 2;
        if(si <= 0)
            printf("%22d %22d signed int\n", si, (signed int)(si-1));
    }
    while(usi > 0) {
        usi *= 2;
        if(usi <= 0)
            printf("%22d %22u unsigned int\n", usi, (unsigned int)(usi-1));
    }
    while(sl > 0) {
        sl *= 2;
        if(sl <= 0)
            printf("%22ld %22ld signed long\n", sl, (signed long)(sl-1));
    }
    while(ul > 0) {
        ul *= 2;
        if(ul <= 0)
            printf("%22lu %22lu unsigned long\n", ul, (unsigned long)(ul-1));
    }
}


void float_limits()
{
    printf("Radix (base) of exponent representation: %d\n", FLT_RADIX);
    printf("float            double           long double\n");
    printf("%-16d %-16d %-16d Significand size in base FLT_RADIX\n", FLT_MANT_DIG, DBL_MANT_DIG, LDBL_MANT_DIG);
    printf("%-16d %-16d %-16d Significand size in base 10\n", FLT_DIG, DBL_DIG, LDBL_DIG);
    printf("%-16d %-16d %-16d Minimum representable exponent in base FLT_RADIX\n", FLT_MIN_EXP, DBL_MIN_EXP, LDBL_MIN_EXP);
    printf("%-16d %-16d %-16d Minimum representable exponent in base 10\n", FLT_MIN_10_EXP, DBL_MIN_10_EXP, LDBL_MIN_10_EXP);
    printf("%-16d %-16d %-16d Maximum representable exponent in base FLT_RADIX\n", FLT_MAX_EXP, DBL_MAX_EXP, LDBL_MAX_EXP);
    printf("%-16d %-16d %-16d Maximum representable exponent in base 10\n", FLT_MAX_10_EXP, DBL_MAX_10_EXP, LDBL_MAX_10_EXP);
    printf("Float Max: %.0f\n", FLT_MAX);
    printf("Double Max: %.0f\n", DBL_MAX);
    printf("Long Double Max: %.0Lf\n", LDBL_MAX);
    printf("Float Min: %.150f\n", FLT_MIN);
    printf("Double Min: %.1200f\n", DBL_MIN);
    printf("Long Double Min: %.12000Lf\n", LDBL_MIN);
}


void float_computed()
{
    int e, m;
    /* We know that floats are 4 byte with:
           1 bit sign               = s
           8 bit exp (bias 127)     = e
          23 bit mantissa           = m

       Maximums
       Given that floats have an implicit leading value of 1, and all ones in
       the exponent are reserved, this puts the maximum value at
           1 + 1/2 + ... + 1/2^23 * 2^(2^(8-1)-1)
         = (2 - 2^(-m)) * 2^(2^(e-1)-1)
    */
    m = 23;
    e = 7;
    printf("FLT_MAX: %.0f\n", (2-powf(2.0,-m)) * powf(2,powf(2,e)-1));

    m = 52;
    e = 10;
    printf("DBL_MAX: %.0f\n", (2-pow(2.0,-m)) * pow(2,pow(2,e)-1));

    m = 63;
    e = 14;
    printf("LDBL_MAX: %.0Lf\n", (2-powl(2.0,-m)) * powl(2,powl(2,e)-1));

    /* Minimums
       1.0 * the minimum exponent. All zeroes are reserved, so bias - 1 yields
       the minimum degree for the exponent
    */

    m = 23;
    e = 7;
    printf("FLT_MIN: %.150f\n", powf(2,-1*(powf(2,e)-2)));

    m = 52;
    e = 10;
    printf("DBL_MIN: %.1200f\n", pow(2,-1*(pow(2,e)-2)));

    m = 63;
    e = 14;
    printf("LDBL_MIN: %.12000Lf\n", powl(2,-1*(powl(2,e)-2)));

}


int main()
{
    printf("Ranges taken from limits.h:\n");
    int_limits();

    printf("\nRanges taken from direct computation:\n");
    int_computed();

    printf("\nFloating point precisions taken from float.h:\n");
    float_limits();

    printf("\nFloating point precisions taken from IEE754 spec and computed:\n");
    float_computed();

    return 0;
}
