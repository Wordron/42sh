/*
** EPITECH PROJECT, 2023
** output_redirection.c
** File description:
** output_redirections
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int redirect_to_file_single(char *filepath)
{
    int fd = open(filepath, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd == -1) {
        printf("Missing name for redirect.\n");
        return (-1);
    }
    return (fd);
}

int redirect_to_file_double(char *filepath)
{
    int fd = open(filepath, O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd == -1) {
        printf("Missing name for redirect.\n");
        return (-1);
    }
    return (fd);
}
