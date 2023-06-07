/*
** EPITECH PROJECT, 2023
** Mini_shell_2
** File description:
** input_redirections
*/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

static int loop_redirect_twice(char *end)
{
    char *str = NULL;
    size_t len = 0;
    int pipefd[2];

    if (pipe(pipefd) == -1)
        exit(84);
    while (1) {
        end = strtok(end, " \t");
        if (isatty(0) == 1)
            printf("? ");
        if (getline(&str, &len, stdin) == -1)
            return (-1);
        if (strncmp(str, end, strlen(end)) == 0
            && strlen(end) == (strlen(str) - 1)) {
            close(pipefd[1]);
            return (pipefd[0]);
        }
        write(pipefd[1], str, strlen(str));
    }
    return (-1);
}

int redirect_twice(char *end)
{
    if (end == NULL) {
        printf("Missing name for redirect.\n");
        return (-1);
    }
    return (loop_redirect_twice(end));
}

int read_from_a_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY, 0644);

    if (fd == -1) {
        printf("Missing name for redirect.\n");
        return (-1);
    }
    return (fd);
}
