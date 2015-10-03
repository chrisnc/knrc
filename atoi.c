#include <stdio.h>

// atoi: convert s to integer
int my_atoi(const char s[])
{
  int n = 0;
  for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
  {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

int main(void)
{
  const char *s = "100";
  printf("my_atoi(\"%s\") = %d\n", s, my_atoi(s));
}
