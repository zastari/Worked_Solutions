/* KR 1-22: Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column.
 */
#include <stdio.h>

#define FOLDLENGTH 20
#define TABSIZE 8

int main()
{
    int i, line_position;

    line_position = 0;
    while((i=getchar()) != EOF) {
        if(i == '\t')
            line_position += TABSIZE - line_position%TABSIZE;
        else if(i == '\n')
            line_position = 0;
        else
            line_position++;

        if(line_position <= FOLDLENGTH)
            putchar(i);
        else if(i!=' ' && i!='\t') {
            printf("\n%c", i);
            line_position = 1;
        }
    }

    return 0;
}
