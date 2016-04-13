#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

static void stack_init(void);
static double pop(void);
static void push(double);

// Exercise 5-10: expr, page 118
int main(int argc, char **argv)
{
  (void)argc;
  stack_init();

  char *arg;
  double x;
  while ((arg = *++argv))
  {
    switch (arg[0])
    {
    case '+':
      push(pop() + pop());
      break;
    case '-':
      x = pop();
      push(pop() - x);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      x = pop();
      push(pop() / x);
      break;
    default:
      if (isdigit(arg[0]))
      {
        char *rest;
        x = strtod(arg, &rest);
        if (*rest)
        {
          fprintf(stderr, "invalid argument: %s\n", arg);
          return EXIT_FAILURE;
        }
        push(x);
      }
      else
      {
        fprintf(stderr, "invalid argument: %s\n", arg);
        return EXIT_FAILURE;
      }
      break;
    }
  }

  printf("%f\n", pop());

  return EXIT_SUCCESS;
}

static struct vector stack;

static void stack_init(void)
{
  vector_init(&stack, sizeof(double));
}

static void push(double x)
{
  vector_push_back(&stack, &x);
}

static double pop(void)
{
  const double *p = vector_back_const(&stack);
  double d = *p;
  vector_pop_back(&stack);
  return d;
}
