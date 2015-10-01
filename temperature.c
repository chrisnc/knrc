#include <stdio.h>

void fahr_to_celsius_ints(void);
void fahr_to_celsius_floats(void);
void celsius_to_fahr_floats(void);

void fahr_to_celsius_for(void);
void fahr_to_celsius_for_reverse(void);

float fahr_to_celsius(float f);
float celsius_to_fahr(float f);

#define LOWER 0   /* lower limit of temperature scale */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

int main(void)
{
  fahr_to_celsius_ints();
  fahr_to_celsius_floats();
  celsius_to_fahr_floats();
  fahr_to_celsius_for();
  fahr_to_celsius_for_reverse();
}

/* Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
void fahr_to_celsius_ints(void)
{
  int fahr, celsius;

  fahr = LOWER;
  while (fahr <= UPPER)
  {
    celsius = 5 * (fahr - 32) / 9;
    printf("%d\t%d\n", fahr, celsius);
    fahr = fahr + STEP;
  }
}

void fahr_to_celsius_floats(void)
{
  float fahr, celsius;

  // Exercise 1-3.
  printf(" ˚F     ˚C\n");

  fahr = LOWER;
  while (fahr <= UPPER)
  {
    celsius = fahr_to_celsius(fahr);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + STEP;
  }
}

// Exercise 1-4.
void celsius_to_fahr_floats(void)
{
  float celsius;

  printf(" ˚C     ˚F\n");

  celsius = LOWER;
  while (celsius <= UPPER)
  {
    printf("%3.0f %6.1f\n", celsius, celsius_to_fahr(celsius));
    celsius = celsius + STEP;
  }
}

void fahr_to_celsius_for(void)
{
  int fahr;

  for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
  {
    printf("%3d %6.1f\n", fahr, fahr_to_celsius(fahr));
  }
}

// Exercise 1-5.
void fahr_to_celsius_for_reverse(void)
{
  int fahr;

  for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP)
  {
    printf("%3d %6.1f\n", fahr, fahr_to_celsius(fahr));
  }
}

// Exercise 1-15.
float fahr_to_celsius(float f)
{
  return (5.0f / 9.0f) * (f - 32.0f);
}

float celsius_to_fahr(float c)
{
  return (c * (9.0f / 5.0f)) + 32.0f;
}
