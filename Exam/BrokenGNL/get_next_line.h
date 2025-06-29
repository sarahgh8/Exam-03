#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void *ft_memmove(void *dest, void *src, size_t n);
char *ft_strchr(char *s, char c);
size_t ft_strlen(char *s);
int str_append_mem(char **s1, char *s2, size_t size2);
int str_append_str(char **s1, char *s2);
char *get_next_line(int fd);
void *ft_memcpy(void *dest, void *src, size_t n);

#endif
