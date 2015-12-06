/* KR 5-16: Add the -d ("directory order") option, which makes comparisons
 *   only on letters, numbers and blanks. Make sure it works in conjunction
 *   with -f.
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#define MAXLINES 5000
#define OPT_NUMERIC 0x1
#define OPT_REVERSE 0x2
#define OPT_FOLDCASE 0x4
#define OPT_DIR 0x8
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void getdir(char *s, char *t);
void *getcomp(int opts);
void writelines(char *lineptr[], int nlines);
void qsort_lomuto(void *lineptr[], int left, int right, int (*comp)(void *, void *), int opts);
void swap(void *v[], int x, int y);
int numcmp(const char *, const char *);


int main(int argc, char **argv)
{
    int nlines;
    unsigned opts = 0;
    void *comp = NULL;

    while(*++argv != NULL) {
        if((*argv)[0] == '-') {
            while(*++*argv) {
                switch(**argv) {
                    case 'd':
                        opts |= OPT_DIR;
                        break;
                    case 'f':
                        opts |= OPT_FOLDCASE;
                        break;
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

    comp = getcomp(opts);

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_lomuto((void **) lineptr, 0, nlines-1,
                     (int (*)(void *, void *))comp, opts);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Input too large to sort.\n");
        return 1;
    }
}


void *getcomp(int opts)
{
    if(opts & OPT_NUMERIC) {
        return numcmp;
    }
    else if(opts & OPT_FOLDCASE) {
        return strcasecmp;
    }
    else {
        return strcmp;
    }
}


void getdir(char *s, char *t)
{
    char *tp = t;
    while(*s) {
        if(isalnum(*s) || *s == ' ') {
            *tp++ = *s;
        }
        s++;
    }
    *tp = '\0';
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
        if(opts & OPT_DIR) {
            char cx[strlen(v[x]) + 1];
            char cleft[strlen(v[left]) + 1];
            getdir(v[x], cx);
            getdir(v[left], cleft);
            if((*comp)(cx, cleft) * (opts & OPT_REVERSE ? -1 : 1) < 0) {
                swap(v, ++pivot, x);
            }
        }
        else {
    		if((*comp)(v[x], v[left]) * (opts & OPT_REVERSE ? -1 : 1) < 0) {
    			swap(v, ++pivot, x);
    		}
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
