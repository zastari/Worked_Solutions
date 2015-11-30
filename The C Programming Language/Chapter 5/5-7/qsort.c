#include <stdio.h>
#include <string.h>
void swap(char *v[], int x, int y)
{
	char *tmp;
	tmp = v[x];
	v[x] = v[y];
	v[y] = tmp;
}


void qsort_hoare(char *v[], int left, int right)
{
	/* qsort using Hoare's pivot selection */
	char *pivot;
	int x, y;

	/* Recursion exit condition: array has 1 element */
	if(left >= right) {
		return;
	}

	/* Partition the list */
	pivot = v[left];
	x = left - 1;		// Adjust since algorithm requires do-while instead of while
	y = right + 1;

	while(1) {
		do {
			y--;
		} while(strcmp(v[y], pivot) > 0);
		do {
			x++;
		} while(strcmp(v[x], pivot) < 0);

		if(x < y) {
			swap(v, x, y);
		}
		else {
			break;
		}
	}

	qsort_hoare(v, left, y);
	qsort_hoare(v, y+1, right);
}
