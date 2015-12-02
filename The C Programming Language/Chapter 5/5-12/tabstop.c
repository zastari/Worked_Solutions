#include "tabstop.h"
#include <string.h>
#include <stdlib.h>
#define COMPARE(a, b) (((a) > (b)) - ((a) < (b)))

void get_tabstops(int *tabstops, char *tablist)
{
    /* Returns a list of tabstops from a comma separated list, i.e.
     *   "1,2,3,4,5" = { 1, 2, 3, 4, 5 } */
    int i;
    for(i = 0; tablist != NULL && i < TABSTOP_ARRAY_LENGTH-1; i++) {
        if(*tablist == ',') {
            tablist += 1;
        }
        tabstops[i] = atoi(tablist);
        tablist = strpbrk(tablist, ",");
    }
    tabstops[i] = -1;
    qsort(tabstops, (size_t)i, sizeof(int), compare);
}


int *next_tabstop(int *tabstops, int col)
{
    /* Returns a pointer to the first tabstop larger than col or a pointer
     *    to the -1 sentinel value if col is larger than all values. */
    while(*tabstops <= col && *tabstops != -1) {
        tabstops++;
    }
    return tabstops;
}


int compare(const void *a, const void *b)
{
    return COMPARE(*(const int *)a, *(const int *)b);
}
