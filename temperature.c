#include <stdio.h>

void fahr_to_celsius_ints(void);
void fahr_to_celsius_floats(void);
void celsius_to_fahr_floats(void);

int main(void)
{
  fahr_to_celsius_ints();
  fahr_to_celsius_floats();
  celsius_to_fahr_floats();
}

/* Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
void fahr_to_celsius_ints(void)
{
  int fahr, celsius;
  int lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  fahr = lower;
  while (fahr <= upper)
  {
    celsius = 5 * (fahr - 32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + step;
  }
}

void fahr_to_celsius_floats(void)
{
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  /* Exercise 1-3. */
  printf(" ˚F     ˚C\n");

  fahr = lower;
  while (fahr <= upper)
  {
    celsius = (5.0 / 9.0) * (fahr - 32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}

/* Exercise 1-4. */
void celsius_to_fahr_floats(void)
{
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;   /* lower limit of temperature scale */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  printf(" ˚C     ˚F\n");

  celsius = lower;
  while (celsius <= upper)
  {
    fahr = (celsius * (9.0 / 5.0)) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
