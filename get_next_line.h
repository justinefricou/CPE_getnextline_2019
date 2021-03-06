/*
** EPITECH PROJECT, 2019
** get_next_line.h
** File description:
** get_next_line : header
*/

#ifndef READ_SIZE
#define READ_SIZE (10)
#endif

#ifndef DEF_GET_NEXT_LINE
#define DEF_GET_NEXT_LINE

#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd);
int get_buffer(char **buffer, int fd);
int add_buffer_to_line(char *buff, char **line);
int backslash_n_in_str(char *str);
int prepare_buffer(char *buffer, int length_buffer);

#endif //DEF_GET_NEXT_LINE