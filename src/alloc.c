#include <stdio.h>

// alloc example, page 101-102

void *alloc(size_t n);
void afree(void *p);

size_t pstrlen(char *s);

int main(void)
{
  int *x = alloc(sizeof(int));
  *x = 123456;
  printf("*x = %d\n", *x);
  afree(x);
  int *y = alloc(sizeof(int));
  printf("*y = %d\n", *y);

  char s[] = "hello, world";
  printf("pstrlen(\"%s\") = %zu\n", s, pstrlen(s));
}

#define ALLOCSIZE 10000 // size of available space

static char allocbuf[ALLOCSIZE]; // storage for alloc
static char *allocp = allocbuf;  // next free position

// alloc and afree example, page 101-102

void *alloc(size_t n) // return pointer to n characters
{
  size_t remaining = ALLOCSIZE - (size_t)(allocp - allocbuf);
  if (remaining >= n) // if it fits
  {
    void *res = allocp;
    allocp += n;
    return res;
  }
  else // not enough room
  {
    return NULL;
  }
}

void afree(void *p)
{
  char *bp = p;
  if (bp >= allocbuf && bp < allocbuf + ALLOCSIZE)
  {
    allocp = bp;
  }
}

// strlen example using pointer arithmetic, page 103
size_t pstrlen(char *s)
{
  char *p = s;
  while (*p)
  {
    ++p;
  }
  return (size_t)(p - s);
}
