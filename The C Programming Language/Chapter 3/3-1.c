/* KR 3-1: Our binary search makes two tests inside the loop, when one
 * would suffice (at the price of more tests outside). Write a version with only one
 * test inside the loop and measure the difference in run time.
 *
 * Results: binsearch_outer is slower by a constant factor based on the index
 * which is being looked up. The difference decreases the larger the index.
 */
#include <stdio.h>
#include <time.h>

#define NSAMPS 100000000

int binsearch(const int x, const int v[], const int n);
int binsearch_outer(const int x, const int v[], const int n);

int binsearch(const int x, const int v[], const int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    while(low <= high) {
        mid = (low+high)/2;
        if(x < v[mid])
            high = mid-1;
        else if(x > v[mid])
            low = mid+1;
        else
            return mid;
    }

    return -1;
}


int binsearch_outer(const int x, const int v[], const int n)
{
    int low, high, mid;
    low = 0;
    high = n-1;
    mid = (low+high)/2;

    while(low <= high && v[mid] != x) {
        mid = (low+high)/2;
        if(x < v[mid])
            high = mid-1;
        else
            low = mid+1;
    }

    return (v[mid] == x) ? mid : -1;
}


int main ()
{
    const int v[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597};
    const int n = (int)(sizeof(v) / sizeof(int));     /* Dynamically calculate elements in v */
    const int x = 1597;

    int result, i;
    clock_t start, end;

    start = clock();
    for(i = 0; i < NSAMPS; i++)
        result = binsearch_outer(x, v, n);
    end = clock();
    printf("binsearch_outer (%d runs) result: %d\n", NSAMPS, result);
    printf("CPU clock time: %.9f\n", (float)(end - start)/(float)CLOCKS_PER_SEC);

    start = clock();
    for(i = 0; i < NSAMPS; i++)
        result = binsearch(x, v, n);
    end = clock();
    printf("binsearch (%d runs) result: %d\n", NSAMPS, result);
    printf("CPU clock time: %.9f\n", (float)(end - start)/(float)CLOCKS_PER_SEC);

    return 0;
}
