/* KR 5-8: There is no error checking on day_of_year or month_day, remedy this
 *   defect.
 */
#include <stdio.h>
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};


int is_leap_year(int year)
{
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}


int day_of_year(int year, int month, int day)
{
    int leap = is_leap_year(year), i;

    /* Sanity check month */
    if(month < 1 || month > 12) {
        return -1;
    }

    /* Sanity check day */
    if(day < 1 || day > daytab[leap][month]) {
        return -1;
    }

    for(i = 1; i < month; i++) {
        day += daytab[leap][i];
    }

    return day;
}


void month_day(int year, int day, int *m, int *d)
{
    int leap = is_leap_year(year), i;

    if((day > 365 && leap == 0) || (day > 366 && leap == 1)) {
        *m = *d = -1;
        return;
    }

    for(i = 1; day > daytab[leap][i]; i++) {
        day -= daytab[leap][i];
    }
    *m = i;
    *d = day;
}


int main(void)
{
    printf("%d %d %d\n", day_of_year(2000, 3, 3), day_of_year(2100, 3, 3), day_of_year(2015, 3, 3));
    printf("%d %d %d\n", day_of_year(2000, 0, 1), day_of_year(2015, 2, 29), day_of_year(2015, 12, 60));

    int m = 0, d = 0;
    month_day(2000, 63, &m, &d);
    printf("%d %d\n", m, d);

    month_day(2007, 366, &m, &d);
    printf("%d %d\n", m, d);

    month_day(2100, 300, &m, &d);
    printf("%d %d\n", m, d);

    return 0;
}
