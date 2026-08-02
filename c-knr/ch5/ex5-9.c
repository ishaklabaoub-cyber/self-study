#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

#define leap(y) ((y)%4 == 0 && (y)%100 != 0 || (y)%400 == 0)

/* day_of_year: set day of year from month & day, with validation */
int day_of_year(int year, int month, int day)
{
    int i, leapyear;

    leapyear = leap(year);

    if (month < 1 || month > 12) {
        printf("day_of_year: invalid month %d\n", month);
        return -1;
    }
    if (day < 1 || day > *(*(daytab+leapyear) + month)) {
        printf("day_of_year: invalid day %d for month %d\n", day, month);
        return -1;
    }

    for (i = 1; i < month; i++)
        day += *(*(daytab+leapyear) + i);

    return day;
}

/* month_day: set month, day from day of year, with validation */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leapyear;

    leapyear = leap(year);

    if (yearday < 1 || yearday > (leapyear ? 366 : 365)) {
        printf("month_day: invalid yearday %d\n", yearday);
        return -1;
    }

    for (i = 1; yearday > *(*(daytab+leapyear) + i); i++)
        yearday -= *(*(daytab + leapyear) + i);

    *pmonth = i;
    *pday = yearday;

    return 0;
}
