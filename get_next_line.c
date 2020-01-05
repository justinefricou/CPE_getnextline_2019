/*
** EPITECH PROJECT, 2019
** get_next_line.c
** File description:
** Returns a read line from a file descriptor.
*/

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line = NULL;

    if (READ_SIZE <= 0 || fd < 0)
        return (NULL);
    do {
        if (get_buffer(&buffer, fd) == 84)
            return (NULL);
        if (add_buffer_to_line(buffer, &line) == 84) {
            free(buffer);
            return (NULL);
        }
        if (backslash_n_in_str(line))
            return (line);
    } while (buffer != NULL);
    return (line);
}

int get_buffer(char **buffer, int fd)
{
    int nb_chars_read = 0;

    if (*buffer != NULL && *buffer[0] != 0)
        return (0);
    if (*buffer == NULL) {
        *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
        if (*buffer == NULL)
            return (84);
    }
    nb_chars_read = read(fd, *buffer, READ_SIZE);
    if (nb_chars_read <= 0) {
        free(*buffer);
        *buffer = NULL;
    }
    return (0);
}

int add_buffer_to_line(char *buff, char **line)
{
    char *new_line = NULL;
    int len_buff = 0;
    int len_line = 0;

    if (buff != NULL)
        for (; buff[len_buff] != '\n' && buff[len_buff] != 0; len_buff++);
    if (*line != NULL)
        for (; (*line)[len_line] != '\n' && (*line)[len_line] != 0; len_line++);
    new_line = malloc(sizeof(char) * (len_buff + len_line + 1));
    if (new_line == NULL)
        return (84);
    for (int i = 0; i < len_line; i++)
        new_line[i] = (*line)[i];
    for (int i = 0; i < len_buff + 1; i++)
        new_line[i + len_line] = buff[i];
    free(*line);
    *line = new_line;
    prepare_buffer(buff, len_buff);
    return (0);
}

int backslash_n_in_str(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '\n') {
            str[i] = 0;
            return (1);
        }
    }
    return (0);
}

int prepare_buffer(char *buffer, int l_prev_buff)
{
    int l_buff = 0;
    int l_new_buff = 0;

    for (; buffer[l_buff] != 0; l_buff++);
    for (int i = l_prev_buff + 1; buffer[i] != 0; i++, l_new_buff++);
    for (int i = 0; i < l_new_buff; i++)
        buffer[i] = buffer[i + l_prev_buff + 1];
    for (int i = 0; i < l_prev_buff + 1; i++)
        buffer[i + l_new_buff] = 0;
    return (0);
}