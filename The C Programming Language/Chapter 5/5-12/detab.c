/* KR 5-12: Extend entab and detab to accept the shorthand
 *    detab -m +n
 *
 *    to mean tab stops every n columns, starting at column m. Choose
 *    convenient (for the user) default behavior.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabstop.h"
#define TABSIZE 8

void detab_fixed(offset, width)
{
    char c;
    int col = 0;
    while((c = getchar()) != EOF) {
        if(c == '\t') {
            do {
                putchar(' ');
                col++;
            } while((col - offset) % width !=  0 || col < offset);
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
                    putchar(' ');
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
    int use_fixed = 0, use_list = 0;
    int offset = 0, width = TABSIZE;
    int tabstops[TABSTOP_ARRAY_LENGTH];
    tabstops[0] = -1;

    while(*++argv != NULL) {
        if((*argv)[0] == '-') {
            if((*argv)[1] == 't') {
                use_list = 1;
                get_tabstops(tabstops, *++argv);
            }
            else if(isdigit((*argv)[1])) {
                use_fixed = 1;
                offset = atoi(*argv + 1);
            }
        }
        else if((*argv)[0] == '+') {
            if(isdigit((*argv)[1])) {
                use_fixed = 1;
                width = atoi(*argv + 1);
            }
        }
    }


    if(use_fixed == 1 && use_list == 1) {
        printf("-t and (-m +n) arguments are mutually exclusive.\n");
        return 1;
    }

    if(use_list == 1) {
        detab_list(tabstops);
    } else {
        detab_fixed(offset, width);
    }

    return 0;
}
