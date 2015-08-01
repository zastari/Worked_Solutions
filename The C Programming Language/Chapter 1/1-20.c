/* KR 1-18: Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set
 * of tab stops, say every n columns. Should n be a variable or a symbolic
 * parameter?
 */
#include <stdio.h>

#define TABSIZE 8

int main()
{
    int c, col;

    col = 0;
    while((c=getchar()) != EOF) {
        if(c == '\t') {
            do {
                putchar(' ');
                col++;
            } while(col%TABSIZE !=  0);
        }
        else {
            putchar(c);
            col++;
            if(c == '\n')
                col = 0;
        }
    }

    return 0;
}
