#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Section 5.12: Complicated Declarations
// dcl program example, page 123

#define MAXTOKEN 100

enum
{
  NAME,
  PARENS,
  BRACKETS
};

static int gettoken(void);

static int getch(void)
{
  return getc(stdin);
}

static void ungetch(int c)
{
  ungetc(c, stdin);
}

static int tokentype;
static char token[MAXTOKEN];
static char name[MAXTOKEN];
static char datatype[MAXTOKEN];
static char out[1000];

static void dirdcl(void);

static void dcl(void)
{
  int ns;
  for (ns = 0; gettoken() == '*'; ++ns)
  {
  }
  dirdcl();
  while (ns-- > 0)
  {
    strcat(out, " pointer to");
  }
}

static void dirdcl(void)
{
  int type;
  if (tokentype == '(')
  {
    dcl();
    if (tokentype != ')')
    {
      printf("error: missing )\n");
    }
  }
  else if (tokentype == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    printf("error: expected name or (dcl)\n");
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS)
  {
    if (type == PARENS)
    {
      strcat(out, " function returning");
    }
    else
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

// dcl: convert declaration to words, page 125
static int main_dcl(void)
{
  while (gettoken() != EOF)
  {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
    {
      printf("syntax error\n");
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

// undcl: convert word description to declaration, page 126
// Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
// declarations.
static int main_undcl(void)
{
  int type;
  int npointer = 0;
  char temp[MAXTOKEN];

  while (gettoken() != EOF)
  {
    strcpy(out, token);
    while ((type = gettoken()) != '\n' && type != EOF)
    {
      switch (type)
      {
      case '*':
        ++npointer;
        break;

      case PARENS:
      case BRACKETS:
      case NAME:
        if (npointer)
        {
          temp[0] = '\0';
          while (npointer > 0)
          {
            strcat(temp, "*");
            --npointer;
          }
          strcat(temp, out);
          if (type == PARENS || type == BRACKETS)
          {
            sprintf(out, "(%s)", temp);
          }
          else
          {
            strcpy(out, temp);
          }
        }
        if (type == NAME)
        {
          sprintf(temp, "%s %s", token, out);
          strcpy(out, temp);
        }
        else
        {
          strcat(out, token);
        }
        break;

      default:
        printf("invalid input at %s\n", token);
        break;
      }
    }
    printf("%s\n", out);
  }
  return 0;
}

int main(int argc, char **argv)
{
  if (argc > 1 && strcmp(argv[1], "-u") == 0)
  {
    return main_undcl();
  }
  return main_dcl();
}

static int gettoken(void)
{
  int c;
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t')
  {
  }
  if (c == '(')
  {
    if ((c = getch()) == ')')
    {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else
    {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if (c == '[')
  {
    // Exercise 5-18. Make dcl recover from input errors.
    // Not checking for EOF in the original causes a crash.
    // TODO: probably need more extensive changes to make dcl robust
    // to invalid input.
    for (*p++ = (char)c; (c = getch()) != EOF && (*p++ = (char)c) != ']';)
    {
    }
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c))
  {
    for (*p++ = (char)c; isalnum(c = getch());)
    {
      *p++ = (char)c;
    }
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  else
  {
    return tokentype = c;
  }
}
