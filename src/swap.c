#include <stdio.h>

// Exercise 4-14. page 91
#define swap(t, x, y)                                                          \
  do                                                                           \
  {                                                                            \
    t swap_tmp = x;                                                            \
    x = y;                                                                     \
    y = swap_tmp;                                                              \
  } while (0)

int main(void)
{
  int x = 100;
  int y = 200;
  printf("x = %d, y = %d\n", x, y);
  swap(int, x, y);
  printf("x = %d, y = %d\n", x, y);
  return 0;
}
