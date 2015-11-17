#ifndef STRS_H
#define STRS_H

void squeeze(char s[], int c);
void my_strcat(char s[], char t[]);
void squeeze_str(char s[], char e[]);
int any(const char s[], const char t[]);
int strrindex(const char *s, const char *t);
void strcat_ptr(char *s, const char *t);
int strend(const char *s, const char *t);
char *my_strncpy(char *s, const char *t, size_t n);
char *my_strncat(char *s, const char *t, size_t n);
int my_strncmp(const char *s, const char *t, size_t n);

#endif // STRS_H
