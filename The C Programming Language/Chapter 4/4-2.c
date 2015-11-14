/* KR 4-2: Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent
 */
#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

double atof(char s[])
{
    double val, power;
    int sign, expsign, expval, i;

    // Whitespace and sign
    for(i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '-' || s[i] == '+') {
        i++;
    }

    // Whole digit component
    for(val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    // Decimal component
    if(s[i] == '.') {
        i++;
    }
    for(power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    // Trailing exponent
    if(s[i] == 'e' || s[i] == 'E') {
        i++;
    }
    expsign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '-' || s[i] == '+') {
        i++;
    }

    for(expval = 0; isdigit(s[i]); i++) {
        expval = 10 * expval + (s[i] - '0');
    }

    if(expsign == -1) {
        for(int j = 0; j < expval; j++) {
            power *= 10.0;
        }
    }
    else if(expsign == 1) {
        for(int j = 0; j < expval; j++) {
            power /= 10.0;
        }
    }
    
    return sign * val / power;
}


int main()
{
    printf("%f\n", atof("-125.34e-3"));
    return 0;
}