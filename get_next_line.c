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
    int length_new_chunk = 0;
    int length_line = 0;

    for ( ; buffer[i] != '\n' && buffer[i] != 0; length_new_chunk++);
    if (line != NULL)
        for ( ; line[length_line] != 0; length_line++);
    *line = malloc(sizeof(char) * (length_new_chunk + length_line + 1));
    if (*line == NULL)
        return (84);
    for (int i = 0; i < length_new_chunk; i++)
        (*line)[length_line + i] = buffer[i];
    (*line)[length_line + length_new_chunk] = 0;
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
}