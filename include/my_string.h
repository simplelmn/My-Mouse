#ifndef MY_STRING_H
#define MY_STRING_H
#include <stdbool.h>
#define MAX_SIZE 2000

void my_memset(bool *buf, bool b, unsigned long n);
int my_size(const char *string);
int my_atoi(const char *string);
bool is_number(char c);
char *my_readline(int fd);
int count_line(int fd);

#endif