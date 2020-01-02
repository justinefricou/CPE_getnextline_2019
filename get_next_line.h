/*
** EPITECH PROJECT, 2019
** get_next_line.h
** File description:
** get_next_line : header
*/

#ifndef DEF_GET_NEXT_LINE
#define DEF_GET_NEXT_LINE

#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE (10)

char *get_next_line(int fd);
int get_buffer(char **buffer, int fd);
int add_buffer_to_line(char *buff, char **line);
int backslash_n_in_str(char *str);
int prepare_buffer(char *buffer, int length_buffer);

/*char *get_next_line(int fd);
int get_chunk_of_file(int fd, char **buffer, char **line);
int get_buffer(char **buffer, int fd);
int put_buffer_in_line(char *buffer, char **line) ;
int backslash_n_in_str(char *str);*/

#endif //DEF_GET_NEXT_LINE