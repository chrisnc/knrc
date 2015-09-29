#include <stdio.h>

// copy input to output; 1st version
void copy_in_to_out_first_version(void)
{
  int c;

  c = getchar();
  while (c != EOF)
  {
    putchar(c);
    c = getchar();
  }
}

// copy input to output; 2nd version
void copy_in_to_out(void)
{
  int c;
  while ((c = getchar()) != EOF)
  {
    putchar(c);
  }
}

// Exercise 1-6.
void getchar_eof_compare(void)
{
  printf("%d\n", getchar() != EOF);
  printf("%d\n", getchar() != EOF);
}

// Exercise 1-7.
void value_of_eof(void)
{
  printf("%d\n", EOF);
}

// count characters in input; 1st version
void count_chars_first(void)
{
  long nc = 0;
  while (getchar() != EOF)
  {
    ++nc;
  }
  printf("%ld\n", nc);
}

// count characters in input; 2nd version
void count_chars(void)
{
  double nc;
  for (nc = 0.0; getchar() != EOF; ++nc)
  {
  }
  printf("%.0f\n", nc);
}

void count_lines(void)
{
  int c, nl;
  nl = 0;
  while ((c = getchar()) != EOF)
  {
    if (c == '\n')
    {
      ++nl;
    }
  }
  printf("%d\n", nl);
}

// Exercise 1-8.
void count_whitespace(void)
{
  int c, nw;
  nw = 0;
  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\t' || c == '\n')
    {
      ++nw;
    }
  }
  printf("%d\n", nw);
}

// Exercise 1-9.
void copy_remove_dup_whitespace(void)
{
  int c;
  int not_blank, last_not_blank = 1;
  while ((c = getchar()) != EOF)
  {
    not_blank = c != ' ';
    if (not_blank || last_not_blank)
    {
      putchar(c);
    }
    last_not_blank = not_blank;
  }
}

// Exercise 1-10.
void copy_escape(void)
{
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == '\t')
    {
      printf("\\t");
    }
    else if (c == '\b')
    {
      printf("\\b");
    }
    else if (c == '\\')
    {
      printf("\\\\");
    }
    else
    {
      putchar(c);
    }
  }
}

int main(void)
{
  copy_escape();
}
