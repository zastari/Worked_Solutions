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

void detab_fixed()
{
    char c;
    int col = 0;
    while((c = getchar()) != EOF) {
        if(c == '\t') {
            do {
                putchar(' ');   /* Make this visible for testing */
                col++;
            } while(col % TABSIZE !=  0);
        }
        else {
            putchar(c);
            col++;
            if(c == '\n')
                col = 0;
        }
    }
}


void detab_list(int *tabstops)
{
    char c;
    int col = 0;
    while((c = getchar()) != EOF) {
        if(c == '\t') {
            if(*(tabstops = next_tabstop(tabstops, col)) != -1) {
                while(col < *tabstops) {
                    putchar(' ');   /* Make this visible for testing */
                    col++;
                }
            }
            else {
                putchar('\t');  /* No more tab stops in list; ignore detabbing */
            }
        }
        else {
            putchar(c);
            col++;
            if(c == '\n') {
                col = 0;
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
        detab_fixed();
    } else {
        detab_list(tabstops);
    }

    return 0;
}
