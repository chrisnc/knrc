#include <stdio.h>
#include <ctype.h>

// atof: convert string s to double
static double atof(const char *s)
{
  int i;
  for (i = 0; isspace(s[i]); ++i) // skip white space
  {
  }
  int sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
  {
    ++i;
  }

  double val;
  for (val = 0.0; isdigit(s[i]); ++i)
  {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i] == '.')
  {
    ++i;
  }

  double power;
  for (power = 1.0; isdigit(s[i]); ++i)
  {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }
  return sign * val / power;
}

int main(void)
{
  const char s[3][20] = {"-100.390", "   102", "+239.21340"};
  for (size_t i = 0; i < 3; ++i)
  {
    printf("atof(\"%s\") = %f\n", s[i], atof(s[i]));
  }
}
