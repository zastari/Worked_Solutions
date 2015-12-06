/* KR 5-13: Write the program tail, which prints the last n lines of its
 *    input. By default, n is 10, let us say, but it can be changed by an
 *    optional argument, so that
 *
 *        tail -n
 *
 *    prints the last n lines. The program should behave rationally no matter
 *    how unreasonable the input or the value of n. Write the program so it
 *    makes the best use of available storage; lines should be stored as in the
 *    sorting program of Section 5.6, not in a two-dimensional array of fixed
 *    size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LINES 10
#define MAXLINES 10000

void tail(int line_count)
{
    size_t n;
    int i, j;
    char *line = NULL;
    char *lines[line_count];
    for(i = 0; i < line_count; i++) {
        lines[i] = NULL;
    }

    for(i = 0; getline(&line, &n, stdin) != -1; i = (i+1) % line_count) {
        lines[i] = line;
        line = NULL;
    }

    j = lines[i] == NULL ? 0 : i;
    if(lines[j] != NULL) {
        do {
            printf("%s", lines[j++]);
            if(j == line_count) {
                j = 0;
            }
        } while(j != i && lines[j] != NULL);
    }
}


int main(int argc, char **argv)
{
    int line_count = LINES;

    while(*++argv != NULL) {
        if((*argv)[0] == '-' && isdigit((*argv)[1])) {
            line_count = atoi(*argv + 1);
            if(line_count > MAXLINES) {
                printf("line count > %d; adjusting to %d\n", MAXLINES, MAXLINES);
                line_count = MAXLINES;
            }
        }
        else {
            printf("Invalid argument %s, ignoring.\n", *argv);
        }
    }

    tail(line_count);
    return 0;
}
