/*  K&R Quicksort
 *  Deeper investigation into the qsort algorithm provided on p. 87 of 2nd ed.
 *  Implements Lomuto's and Hoare's partitioning method and compares their
 *  execution speeds against randomized arrays
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000
#define ARRAY_MODULUS 10000
#define NUM_RUNS 10000

void qsort_lomuto(int[], int, int);
void swap(int[], int, int);
void print_i(int[]);
double run_loop(void (*qsort)(int [], int, int), unsigned seed, int runs);


void swap(int i[], int x, int y)
{
	int tmp;
	tmp = i[x];
	i[x] = i[y];
	i[y] = tmp;
}


void qsort_lomuto(int i[], int left, int right)
{
	/* qsort using Lomuto's pivot selection */
	int pivot;

	/* Recursion exit condition: array has 1 element */
	if(left >= right) {
		return;
	}

	/* Select pivot and move it to i[left]*/
	swap(i, left, (right-left)/2 + left);

	/* Partition the list */
	pivot = left;
	for(int x = left+1; x <= right; x++) {
		if(i[x] < i[left]) {
			swap(i, ++pivot, x);
		}
	}
	swap(i, pivot, left); // Move pivot from i[left] to the end of its partition

	/* qsort_lomuto each side of pivot */
	qsort_lomuto(i, left, pivot-1);
	qsort_lomuto(i, pivot+1, right);
}


void qsort_hoare(int i[], int left, int right)
{
	/* qsort using Hoare's pivot selection */
	int pivot;
	int x, y;

	/* Recursion exit condition: array has 1 element */
	if(left >= right) {
		return;
	}

	/* Partition the list */
	pivot = i[left];
	x = left - 1;		// Adjust since algorithm requires do-while instead of while
	y = right + 1;

	while(1) {
		do {
			y--;
		} while(i[y] > pivot);
		do {
			x++;
		} while(i[x] < pivot);

		if(x < y) {
			swap(i, x, y);
		}
		else {
			break;
		}
	}

	qsort_hoare(i, left, y);
	qsort_hoare(i, y+1, right);
}


void print_i(int i[])
{
	for(int j = 0; j < ARRAY_SIZE; j++) {
		printf("%d ", i[j]);
	}
	printf("\n");
}


double run_loop(void (*qsort)(int [], int, int), unsigned seed, int runs)
{
	double execution_time = 0.0;
	clock_t start, end;
	int i[ARRAY_SIZE];

  	srand(seed);
	for(int run = 0; run < runs; run++) {
    	for(int x = 0; x < ARRAY_SIZE; x++) {
    		i[x] = rand() % ARRAY_MODULUS;
    	}
		start = clock();
		qsort(i, 0, ARRAY_SIZE);
		end = clock();
		execution_time += (double)(end - start)/CLOCKS_PER_SEC;
	}

	return execution_time;
}


int main(void)
{
	printf("Comparing qsort using Lomuto and Hoare's partitioning methods for %d runs\n", NUM_RUNS);
	printf("Test arrays: %d elements in range 0 - %d\n", ARRAY_SIZE, ARRAY_MODULUS-1);
	printf("Lomuto. Total: %lf\n", run_loop(qsort_lomuto, 0, NUM_RUNS));
	printf("Hoare. Total: %lf\n", run_loop(qsort_hoare, 0, NUM_RUNS));
	return 0;
}
