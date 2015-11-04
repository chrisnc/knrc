#include <stdio.h>

// shellsort: sort v[0]...v[n-1] into increasing order
static void shellsort(int v[], int n)
{
  int gap, i, j, temp;
  for (gap = n / 2; gap > 0; gap /= 2)
  {
    for (i = gap; i < n; ++i)
    {
      for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
      {
        temp = v[j];
        v[j] = v[j + gap];
        v[j + gap] = temp;
      }
    }
  }
}

#define ARRAY_SIZE 10

int main(void)
{
  int x[ARRAY_SIZE] = {5,2,9,12,3,12,30,-1,-900,2149};
  shellsort(x, ARRAY_SIZE);
  for (int i = 0; i < ARRAY_SIZE; ++i)
  {
    printf("%d ", x[i]);
  }
  printf("\n");
}
