#include <stdio.h>
#include <stdbool.h>

// date conversion example, page 111
// Exercise 5-8. page 112
// added error checking to day_of_year and month_day

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

static int is_leap_year(int year)
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

// day_of_year: determine day of year from month & day
static int day_of_year(int year, int month, int day)
{
  int leap = is_leap_year(year);
  if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month])
  {
    fprintf(stderr, "day_of_year: invalid date %d/%d/%d\n", year, month, day);
    return -1;
  }
  for (int i = 1; i < month; ++i)
  {
    day += daytab[leap][i];
  }
  return day;

  // Exercise 5-9. page 114
  // version using pointer arithmetic, commented out because it's harder to
  // understand
  /*
  for (char *dpm = daytab[leap] + 1; dpm < daytab[leap] + month; ++dpm)
  {
    day += *dpm;
  }
  */
}

// month_day: set month, day from day of year
static void month_day(int year, int yearday, int *pmonth, int *pday)
{
  int leap = is_leap_year(year);
  if (yearday < 1 || yearday > 365 + leap)
  {
    fprintf(stderr, "month_day: invalid yearday %d for year %d\n", yearday,
            year);
    *pmonth = -1;
    *pday = -1;
    return;
  }
  int i;
  for (i = 1; yearday > daytab[leap][i]; ++i)
  {
    yearday -= daytab[leap][i];
  }
  *pmonth = i;
  *pday = yearday;

  // Exercise 5-9. page 114
  // version using pointer arithmetic, commented out because it's harder to
  // understand
  /*
  char *dpm;
  for (dpm = daytab[leap] + 1; yearday > *dpm; ++dpm)
  {
    yearday -= *dpm;
  }
  *pmonth = (char)(dpm - daytab[leap]);
  */
}

// month_name: return name of the given month (1-12)
static const char *month_name(int m)
{
  static const char *names[] = {
      "Illegal month", "January",  "February", "March",  "April",
      "May",           "June",     "July",     "August", "September",
      "October",       "November", "December",
  };

  return (m < 1 || m > 12) ? names[0] : names[m];
}

int main(void)
{
  struct
  {
    int y;
    int m;
    int d;
  } ymd_tests[8] = {
      {1990, 5, 23}, {1986, 1, 23}, {1887, 2, 28},  {2015, 10, 31},
      {2012, 2, 29}, {1887, 2, 29}, {2015, -3, 31}, {2012, 4, 35},
  };

  for (size_t i = 0; i < 8; ++i)
  {
    int yday = day_of_year(ymd_tests[i].y, ymd_tests[i].m, ymd_tests[i].d);
    if (yday < 0)
    {
      continue;
    }
    int m, d;
    month_day(ymd_tests[i].y, yday, &m, &d);
    if (m != ymd_tests[i].m || d != ymd_tests[i].d)
    {
      fprintf(stderr, "mismatched month/day after day_of_year -> month_day "
                      "expected %d/%d, got %d/%d\n",
              ymd_tests[i].m, ymd_tests[i].d, m, d);
      continue;
    }
    printf("day_of_year(%d, %d, %d) = %d\n", ymd_tests[i].y, ymd_tests[i].m,
           ymd_tests[i].d, yday);
    printf("month_day(%d, %d) = (%d, %d)\n", ymd_tests[i].y, yday, m, d);
    printf("month_name(%d) = \"%s\"\n", m, month_name(m));
  }

  struct
  {
    int y;
    int yday;
  } yday_tests[7] = {
      {1990, 230}, {1986, 1},  {1887, 60},  {2015, 366},
      {2012, 60},  {1887, -3}, {2012, 366},
  };

  for (size_t i = 0; i < 7; ++i)
  {
    int m, d;
    month_day(yday_tests[i].y, yday_tests[i].yday, &m, &d);
    printf("month_name(%d) = \"%s\"\n", m, month_name(m));
    if (m < 0 || d < 0)
    {
      continue;
    }
    int yday = day_of_year(yday_tests[i].y, m, d);
    if (yday != yday_tests[i].yday)
    {
      fprintf(stderr, "mismatched day of year after month_day -> day_of_year "
                      "expected %d, got %d\n",
              yday_tests[i].yday, yday);
      continue;
    }
    printf("month_day(%d, %d) = (%d, %d)\n", yday_tests[i].y,
           yday_tests[i].yday, m, d);
    printf("day_of_year(%d, %d, %d) = %d\n", yday_tests[i].y, m, d,
           yday_tests[i].yday);
  }

  return 0;
}
