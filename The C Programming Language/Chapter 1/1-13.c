// KR 1-13: Write a program to print a histogram of the length of words in its
// input. It is easy to draw the histogram with the bars horizontal;
// a vertical orientation is more challenging.
//
// Compilation Notes: Requires -lm
#include <stdio.h>
#include <math.h>

#define MAX_WORD_LEN 15
#define SCALE_MAX_LENGTH 20

// orientation: 0 = horizontal; 1 = vertical, 2 = both
void print_histogram(int wordsize[], int orientation);
int is_whitespace(int c);


int is_whitespace(int c)
{
    if(c == ' ' || c == '\t' || c == '\n')
        return 1;
    return 0;
}


void print_histogram(int wordsize[MAX_WORD_LEN], int orientation)
{
    int i, j, scale, maxcount;

    maxcount = 0;
    for(i = 0; i < MAX_WORD_LEN; ++i) {
        if(wordsize[i] > maxcount)
            maxcount = wordsize[i];
    }
    scale = ceil((float)maxcount / SCALE_MAX_LENGTH);

    if(orientation == 0 || orientation == 2) {                          // Horizontal case
        for(i = 0; i < MAX_WORD_LEN; ++i) {
            if(i < (MAX_WORD_LEN - 1))
                printf("%3d: ", i+1);
            else
                printf("%2d+: ", i+1);
            for(j = 0; j < wordsize[i]; j += scale)
                putchar('|');
            putchar('\n');
        }
        printf("Histogram of word length in input (horizontal)\n");
    }
    if(orientation == 1 || orientation == 2) {                          // Vertical case
        for(j = maxcount; j > 0; j -= scale) {
            for(i = 0; i < MAX_WORD_LEN; ++i) {
                if (wordsize[i] >= j)
                    printf("___ ");
                else
                    printf("    ");
            }
            putchar('\n');
        }

        for(i = 0; i < (MAX_WORD_LEN-1); ++i)
                printf("%2d  ", i+1);
        printf("%2d+\n", i+1);
        printf("Histogram of word length in input (vertical)\n");
    }

    printf("One unit =  %d occurrences (rounded up)\n", scale);
}

int main()
{
    int c, i, prevc, curlen;
    int wordsize[MAX_WORD_LEN];
    prevc = curlen = 0;

    for(i = 0; i < MAX_WORD_LEN; ++i)
        wordsize[i] = 0;

    while((c = getchar()) != EOF) {
        if(is_whitespace(c)) {
            if(!is_whitespace(prevc)) {
                if(curlen <= MAX_WORD_LEN-1)
                    ++wordsize[curlen-1];
                else
                    ++wordsize[MAX_WORD_LEN-1];
            }
            curlen = 0;
        }
        else
            ++curlen;

        prevc = c;
    }

    print_histogram(wordsize, 2);

    return 0;
}
