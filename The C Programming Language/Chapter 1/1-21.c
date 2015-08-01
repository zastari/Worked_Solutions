/* KR 1-21: Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the
 * same tab stops as for detab. When either a tab or a single blank would
 * suffice to reach a tab stop, which should be given preference?
 */
#include <stdio.h>

#define TABSIZE 8

int main() {
    int c, i, j, col;

    col = 0;
    while((c=getchar()) != EOF) {
        i = 0;
        if(c == ' ') {
            do {
                i++;
                col++;
            } while(col%TABSIZE != 0 && (c=getchar())==' ');

            if(col % TABSIZE == 0)      /* Give precedence to tab if 1 space = TAB */
                putchar('\t');
            else if(c != '\t') {        /* Only print spaces if a tab isn't in the same block */
                for(j=0; j<i; j++)
                    putchar(' ');
            }
        }
        if(c != ' ') {
            putchar(c);
            col++;
            if(c=='\n' || c=='\t')
                col = 0;
        }
    }

    return 0;
}
