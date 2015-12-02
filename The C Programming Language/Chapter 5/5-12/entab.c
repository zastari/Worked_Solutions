/* KR 5-12: Extend entab and detab to accept the shorthand
 *    entab -m +n
 *
 *    to mean tab stops every n columns, starting at column m. Choose
 *    convenient (for the user) default behavior.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabstop.h"
#define TABSIZE 8

void entab_fixed(offset, width)
{
    int c, buf, col = 0;
    while((c = getchar()) != EOF) {
        if(c == ' ') {
            buf = 0;
            do {
                buf++, col++;
            } while((col < offset || (col - offset) % width != 0) && (c = getchar()) == ' ');

            if((col >= offset) && (col - offset) % width == 0) {
                putchar('x');
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
        entab_list(tabstops);
    } else {
        entab_fixed(offset, width);
    }

    return 0;
}
