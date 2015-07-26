// KR 1-14: Write a program to display the frequencies of different cahracters
// in its input
//
// Compilation Notes: Requires -lm
#include <stdio.h>
#include <math.h>

#define SCALE_MAX_LENGTH 20

// orientation: 0 = horizontal; 1 = vertical, 2 = both
void print_histogram(int char_array[]);

void print_histogram(int char_array[26])
{
    int i, j, scale, maxcount;

    maxcount = 0;
    for(i = 0; i < 26; ++i) {
        if(char_array[i] > maxcount)
            maxcount = char_array[i];
    }
    scale = ceil((float)maxcount / SCALE_MAX_LENGTH);

    for(i = 0; i < 26; ++i) {
        printf("%c: ", (char)('A' + i));
        for(j = 0; j < char_array[i]; j += scale)
            putchar('|');
        putchar('\n');
    }
    printf("Histogram of letter count in input\n");
    printf("One unit = %d occurrences (rounded up)\n", scale);
}

int main()
{
    int c, i;
    int char_array[26];

    for(i = 0; i < 26; ++i)
        char_array[i] = 0;

    while((c = getchar()) != EOF) {
        if((c >= 'A') && (c <= 'Z'))
            ++char_array[c-'A'];
        else if((c >= 'a') && (c <= 'z'))
            ++char_array[(c-32)-'A'];       // Lowercase chars start 32 after upper
    }

    print_histogram(char_array);

    return 0;
}
