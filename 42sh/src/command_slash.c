/*
** EPITECH PROJECT, 2023
** command_slash.c
** File description:
** command_slash
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "minishell.h"

int test_slashes(char *command_line)
{
    for (int i = 0; command_line[i] != '\0'; i++) {
        if (command_line[i] == '/')
            return (1);
    }
    return (0);
}

void command_slash(char **command_line, minishell *mysh)
{
    struct stat st;

    stat(command_line[0], &st);
    if (access(command_line[0], F_OK) == 0 && !S_ISDIR(st.st_mode)) {
        forking(command_line, mysh);
        free_double_array(command_line);
        return;
    }
    if (S_ISDIR(st.st_mode)) {
        printf("%s: Permission denied.\n", command_line[0]);
        mysh->last_status = 1;
    }
    if (!S_ISDIR(st.st_mode)) {
        printf("%s: Command not found.\n", command_line[0]);
        mysh->last_status = 1;
    }
    return;
}
