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
static char temp[MAXTOKEN];
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

// Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
// declarations.
static void show_pointer(char *s, int type, int npointer)
{
  bool need_parens = type == PARENS || type == BRACKETS;
  strcpy(temp, need_parens ? "(" : "");
  while (npointer > 0)
  {
    strcat(temp, "*");
    --npointer;
  }
  strcat(temp, s);
  strcat(temp, need_parens ? ")" : "");
  strcpy(s, temp);
}

// undcl: convert word description to declaration, page 126
static int main_undcl(void)
{
  int type;
  int npointer = 0;

  while (gettoken() != EOF)
  {
    strcpy(out, token);
    while ((type = gettoken()) != '\n' && type != EOF)
    {
      if (type == PARENS || type == BRACKETS)
      {
        if (npointer)
        {
          show_pointer(out, type, npointer);
          npointer = 0;
        }
        strcat(out, token);
      }
      else if (type == '*')
      {
        ++npointer;
      }
      else if (type == NAME)
      {
        if (npointer)
        {
          show_pointer(out, type, npointer);
          npointer = 0;
        }
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      }
      else
      {
        printf("invalid input at %s\n", token);
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
