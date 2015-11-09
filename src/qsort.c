#include <stdio.h>

// quicksort example, page 87

// swap: interchange v[i] and v[j]
static void swap(int v[], size_t i, size_t j)
{
  int temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

// qsort: sort v[0]...v[n-1] into increasing order
static void qsort(int *v, size_t n)
{
  // do nothing if array contains fewer than two elements
  if (n < 2)
  {
    return;
  }

  swap(v, 0, n / 2); // move partition elem
  size_t last = 0;   // to v[0]
  for (size_t i = 0; i < n; ++i)
  {
    if (v[i] < v[0])
    {
      swap(v, ++last, i);
    }
  }
  swap(v, 0, last); // restore partition elem

  qsort(v, last);
  qsort(v + last + 1, n - last - 1);
}

static void print_array(int *v, size_t n)
{
  printf("[");
  if (n > 0)
  {
    for (size_t i = 0; i < n - 1; ++i)
    {
      printf("%d, ", v[i]);
    }
    printf("%d", v[n - 1]);
  }
  printf("]");
}

int main(void)
{
  int x[6] = {4, 10, -12, 30, 1, 3};
  print_array(x, 6);
  printf("\n");
  qsort(x, 6);
  print_array(x, 6);
  printf("\n");
}
