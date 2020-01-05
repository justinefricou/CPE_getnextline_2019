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

    if (READ_SIZE <= 0)
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

int prepare_buffer(char *buffer, int length_buffer)
{
    if (buffer[length_buffer] != '\n') {
        for (int i = 0; i < length_buffer; i++)
            buffer[i] = 0;
        return (0);
    }
    for (int i = length_buffer; buffer[i] != 0; i++)
        buffer[i - length_buffer] = buffer[i];
    buffer[length_buffer] = 0;
}

/*char *get_next_line(int fd)
{
    static char *buffer = NULL;
    char *line = NULL;

    do {
        if (get_chunk_of_file(fd, &buffer, &line) == 84)
            return (NULL);
        if (backslash_n_in_str(line))
            return (line);
    } while (buffer != NULL);
    return (line);
}

int get_chunk_of_file(int fd, char **buffer, char **line)
{
    if (*buffer != NULL && (*buffer)[0] != 0) {
        if (put_buffer_in_line(*buffer, line) == 84)
            return (84);
    } else if (get_buffer(buffer, fd) == 84)
        return (84);
    else {
        if (put_buffer_in_line(*buffer, line) == 84) {
            free(*buffer);
            return (84);
        }
    }
    return (0);
}

int get_buffer(char **buffer, int fd)
{
    int nb_chars_read = 0;

    if (*buffer != NULL) {
        if (backslash_n_in_str(*buffer))
            return (0);
    } else
        *buffer = malloc(sizeof(char) * READ_SIZE + 1);
    nb_chars_read = read(fd, buffer, READ_SIZE);
    if (nb_chars_read < 0) {
        free(buffer);
        return (84);
    } else if (nb_chars_read == 0) {
        free(*buffer);
        *buffer = NULL;
    }
    *buffer[nb_chars_read] = 0;
    return (0);
}

int put_buffer_in_line(char *buffer, char **line) // ne pas mettre \n
{
    int chunk_len = 0;
    int line_len = 0;

    for ( ; buffer[chunk_len] != '\n' && buffer[chunk_len] != 0; chunk_len++);
    if (line != NULL)
        for ( ; line[line_len] != 0; line_len++);
    *line = malloc(sizeof(char) * (chunk_len + line_len + 1));
    if (*line == NULL)
        return (84);
    for (int i = 0; i < chunk_len; i++)
        (*line)[line_len + i] = buffer[i];
    (*line)[line_len + chunk_len] = 0;
    for (int i = 0; i < READ_SIZE; i++)
        buffer[i] = 0;
    return (0);
}

int backslash_n_in_str(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] == '\n')
            return (1);
    }
    return (0);
}*/