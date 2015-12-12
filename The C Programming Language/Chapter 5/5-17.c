/* KR 5-17: Add a field-handling capability, so sorting may be done on fields
 *   within lines, each field sorted according to an independent set of options.
 *
 *   Solution Notes:
 *     The inline flag is passed with -i. If a field has inline flag set, then
 *     individual elements are sorted with a , delimiter.
 *
 *     A field can be specified by including a number as the last argument in
 *     a given flag, i.e.
 *
 *         -df3
 *
 *     will do a fold-case directory sort on the 3rd field
 *
 *     One global field is allowed, an arbitrary number of inline fields are
 *     allowed.
 */
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>

#define MAXLINES 5000
#define MAXELEMENTS 1000
#define MAXOPTS 100

#define OPT_NUMERIC 0x1
#define OPT_REVERSE 0x2
#define OPT_FOLDCASE 0x4
#define OPT_DIR 0x8
#define OPT_INLINE 0x10
#define OPT_SENTINEL 0x20

#define MIN(a,b) ((a) < (b)) ? (a) : (b)

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
int split_fields(char *delimited, char **split);
void getdir(char *s, char *t, size_t n);
char *getfield(char *s, int field, size_t *n);
int comp(char *s1, char *s2, int opts[2]);
void writelines(char *lineptr[], int nlines);
void sort_inplace(int opts[2], int nlines);
void qsort_lomuto(void *lineptr[], int left, int right, int (*fieldopts)[2]);
void swap(void *v[], int x, int y);
int numcmp(const char *, const char *, size_t);


int main(int argc, char **argv)
{
    int nlines;
    int fieldopts[MAXOPTS][2];

    int i;
    for(i = 0; *++argv != NULL; i++) {
        if((*argv)[0] == '-') {
            int field_num = 0;
            int opts = 0;
            while(*++*argv) {
                switch(**argv) {
                    case 'd':
                        opts |= OPT_DIR;
                        break;
                    case 'f':
                        opts |= OPT_FOLDCASE;
                        break;
                    case 'i':
                        opts |= OPT_INLINE;
                        break;
                    case 'n':
                        opts |= OPT_NUMERIC;
                        break;
                    case 'r':
                        opts |= OPT_REVERSE;
                        break;
                    default:
                        if(isdigit(**argv)) {
                            field_num = atoi(*argv);
                        }
                }
            }
            fieldopts[i][0] = field_num;
            fieldopts[i][1] = opts;
        }
    }
    fieldopts[i][0] = -1;
    fieldopts[i][1] = OPT_SENTINEL;

    if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        i = 0;
        do {
            if(fieldopts[i][1] & OPT_INLINE) {
                sort_inplace(*(fieldopts+i), nlines);
            }
            else {
                qsort_lomuto((void **) lineptr, 0, nlines-1, fieldopts);
            }
            i++;
        } while(fieldopts[0][1] != OPT_SENTINEL && fieldopts[i][1] != OPT_SENTINEL);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Input too large to sort.\n");
        return 1;
    }
}


void sort_inplace(int opts[2], int nlines)
{
    int j;
    size_t n = 0;
    for(j = 0; j < nlines; j++) {
        int nfields;
        char *split[MAXELEMENTS];
        char *t = getfield(*(lineptr+j), opts[0], &n);
        nfields = split_fields(t, split);

        int inline_opts[2] = { 0, opts[1] };
        qsort_lomuto((void **) split, 0, nfields-1, &inline_opts);

        int k;
        for(k = 0; k < nfields; k++) {
            int l = 0;
            while(*(*(split+k)+l)) {
                *t++ = *(*(split+k)+l++);
            }
            if(k < nfields - 1) {
                *t++ = ',';
            }
        }
    }
}


int comp(char *s1, char *s2, int opts[2])
{
    int comp_raw;
    int (*comp_func)(const char *, const char *, size_t);
    size_t n, n1 = 0, n2 = 0;

    /* Get comparison method based on flags */
    if(opts[1] & OPT_NUMERIC) {
        comp_func = numcmp;
    }
    else if(opts[1] & OPT_FOLDCASE) {
        comp_func = strncasecmp;
    }
    else {
        comp_func = strncmp;
    }

    /* Set comparison length if sorting on a field */
    if(opts[0] > 0) {
        s1 = getfield(s1, opts[0], &n1);
        s2 = getfield(s2, opts[0], &n2);
        n = MIN(n1, n2);
    }
    else {
        n = MIN(strlen(s1), strlen(s2));
    }

    /* Filter strings if doing dirsort */
    if(opts[1] & OPT_DIR) {
        char t1[n+1];
        char t2[n+1];
        getdir(s1, t1, n);
        getdir(s2, t2, n);
        comp_raw = comp_func(t1, t2, n);
    }
    else {
        comp_raw = comp_func(s1, s2, n);
    }

    /* If two fields in a field sort returned equal, shorter one is first */
    if(comp_raw == 0) {
        if(n1 < n2) {
            comp_raw = -1;
        }
        else if(n1 > n2) {
            comp_raw = 1;
        }
    }

    /* Invert result if reverse is set */
    if(opts[1] & OPT_REVERSE) {
        comp_raw *= -1;
    }
    return comp_raw;
}


void getdir(char *s, char *t, size_t n)
{
    char *tp = t;
    size_t i;
    for(i = 0; *s && i < n; i++) {
        if(isalnum(*s) || *s == ' ') {
            *tp++ = *s;
        }
        s++;
    }
    *tp = '\0';
}


int split_fields(char *delimited, char **split)
{
    int i;
    size_t j;

    i = 0;
    while(*delimited && !isspace(*delimited) && i < MAXELEMENTS) {
        for(j = 0; *(delimited+j) && !isspace(*(delimited+j)) && *(delimited+j) != ','; j++)
            ;

        if(j > 0) {
            *(split+i) = calloc(j, sizeof(char));
            strncpy(*(split+i), delimited, j);
            i++;
        }

        if(!*(delimited+j) || isspace(*(delimited+j))) {
            break;
        }
        else {
            delimited += j + 1;
        }
    }

    return i;
}


char *getfield(char *s, int field, size_t *n)
{
    /* Return a pointer to the given field in string s. If the passed field is
     *   greater than the amount of fields, return a pointer to '\0'.
     *   size_t n is passed by reference to provide the size of the field
     *   that is returned. */
    int i;
    char *t = NULL;

    while(isspace(*s)) {
        /* Skip initial spaces */
        s++;
    }

    /* Advance s to correct field; fields are 1-indexed */
    for(i = 1; *s != '\0' && i < field; i++) {
        while(!isspace(*s) && *s) {
            s++;
        }
        while(isspace(*s) && *s) {
            s++;
        }
    }

    t = s;
    for(*n = 0; !isspace(*s) && *s; (*n)++, s++)
        ;

    return t;
}


void qsort_lomuto(void *v[], int left, int right, int (*fieldopts)[2])
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
        if(comp(v[x], v[left], *fieldopts) < 0) {
            swap(v, ++pivot, x);
        }
	}
	swap(v, pivot, left); // Move pivot from i[left] to the end of its partition

	/* qsort_lomuto each side of pivot */
	qsort_lomuto(v, left, pivot-1, fieldopts);
	qsort_lomuto(v, pivot+1, right, fieldopts);
}


void swap(void *v[], int x, int y)
{
    void *tmp;
    tmp = v[x];
    v[x] = v[y];
    v[y] = tmp;
}


int numcmp(const char *s1, const char *s2, size_t n)
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
