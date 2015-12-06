/* KR 5-14: Modify the sort program to handle a -r flag, which indicates
 *   sorting in reverse (decreasing) order. Be sure that -r works with -n.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000
#define OPT_NUMERIC 0x1
#define OPT_REVERSE 0x2
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_lomuto(void *lineptr[], int left, int right, int (*comp)(void *, void *), int opts);
void swap(void *v[], int x, int y);
int numcmp(const char *, const char *);

int main(int argc, char **argv)
{
    int nlines;
    unsigned opts = 0;

    while(*++argv != NULL) {
        if((*argv)[0] == '-') {
            while(*++*argv) {
                switch(**argv) {
                    case 'n':
                        opts |= OPT_NUMERIC;
                        break;
                    case 'r':
                        opts |= OPT_REVERSE;
                        break;
                }
            }
        }
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_lomuto((void **) lineptr, 0, nlines-1,
                     (int (*)(void *, void *))(opts & OPT_NUMERIC ? numcmp : strcmp), opts);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Input too large to sort.\n");
        return 1;
    }
}


void qsort_lomuto(void *v[], int left, int right, int (*comp)(void *, void *), int opts)
{
	/* qsort using Lomuto's pivot selection */
	int pivot;

	/* Recursion exit condition: array has 1 element */
	if(left >= right) {
		return;
	}

	/* Select pivot and move it to i[left]*/
	swap(v, left, (right-left)/2 + left);

	/* Partition the list */
	pivot = left;
	for(int x = left+1; x <= right; x++) {
		if((*comp)(v[x], v[left]) * (opts & OPT_REVERSE ? -1 : 1) < 0) {
			swap(v, ++pivot, x);
		}
	}
	swap(v, pivot, left); // Move pivot from i[left] to the end of its partition

	/* qsort_lomuto each side of pivot */
	qsort_lomuto(v, left, pivot-1, comp, opts);
	qsort_lomuto(v, pivot+1, right, comp, opts);
}


void swap(void *v[], int x, int y)
{
    void *tmp;
    tmp = v[x];
    v[x] = v[y];
    v[y] = tmp;
}


int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2) {
        return -1;
    }
    else if (v1 > v2) {
        return 1;
    }
    else {
        return 0;
    }
}


int readlines(char *lineptr[], int nlines)
{
    char *line = NULL;
    size_t n;
    int i;

    for(i = 0; getline(&line, &n, stdin) != -1; i++) {
        if(i == nlines) {
            /* Input larger than maximum line count */
            return -1;
        }
        lineptr[i] = line;
        line = NULL;
    }

    return i;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for(i = 0; i < nlines; i++) {
        printf("%s", lineptr[i]);
    }
}
