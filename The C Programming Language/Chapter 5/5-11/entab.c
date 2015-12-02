/* KR 5-11: Modify the programs entab and detab (written as exercises in
 *   Chapter 1) to accept a list of tab stops are arguments. Use the default
 *   tab settings if there are no arguments.
 *
 *   Solution notes: Using -t n_1,n_2,...n_m to take tab arguments. Each
 *     value is a fixed column position, not a difference from the previous
 *     column.
 */
#include <stdio.h>
#include "tabstop.h"
#define TABSIZE 8

void entab_fixed()
{
    int c, buf, col = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            buf = 0;
            do {
                buf++, col++;
            } while(col % TABSIZE != 0 && (c = getchar()) == ' ');

            if(col % TABSIZE == 0) {
                putchar('\t');
            }
            else if(c != '\t') {
                while(buf-- > 0) {
                    putchar(' ');
                }
            }
        }
        if(c != ' ') {
            putchar(c);
            col++;
            if(c == '\n' || c == '\t') {
                col = 0;
            }
        }
    }
}

void entab_list(int *tabstops)
{
    int c, buf, col = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            if(*(tabstops = next_tabstop(tabstops, col)) == -1) {
                /* No more tabstops; ignore entabbing */
                putchar(c);
                continue;
            }

            buf = 0;
            do {
                buf++, col++;
            } while(col < *tabstops && (c = getchar()) == ' ');

            if(col == *tabstops) {
                putchar('\t');
            }
            else if(c != '\t') {
                while(buf-- > 0) {
                    putchar(' ');
                }
            }
        }
        if(c != ' ') {
            putchar(c);
            col++;
            if(c == '\n') {
                col = 0;
            }
            else if(c == '\t') {
                if(*(tabstops = next_tabstop(tabstops, col)) != -1) {
                    col = *tabstops;
                }
            }
        }
    }
}


int main(int argc, char **argv)
{
    int fixed = 1;
    int tabstops[TABSTOP_ARRAY_LENGTH];
    tabstops[0] = -1;

    while(*++argv != NULL) {
        if((*argv)[0] == '-') {
            if((*argv)[1] == 't') {
                fixed = 0;
                get_tabstops(tabstops, *++argv);
            }
        }
    }

    if(fixed == 1) {
        entab_fixed();
    } else {
        entab_list(tabstops);
    }

    return 0;
}
