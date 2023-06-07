/*
** EPITECH PROJECT, 2023
** which.c
** File description:
** which
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

static int which_check_path(char *command_line, minishell *mysh)
{
    char *command = NULL;
    char *temp = strdup(command_line);
    if (temp == NULL)
        exit(84);

    for (int i = 0; mysh->path[i] != NULL; i++) {
        command = NULL;
        command = strcat(strcat(mysh->path[i], "/"), temp);
        strcpy(command_line, command);
        if (access(command_line, F_OK) == 0) {
            printf("%s\n", command_line);
            free(temp);
            return (0);
        }
    }
    return (1);
}

static int main_if_which(char *command_line, minishell *mysh)
{
    for (int i = 0; mysh->alias[i] != NULL; i++) {
        if (strcmp(mysh->alias[i]->alias, command_line) == 0) {
            printf("%s: \t aliased to %s\n", mysh->alias[i]->alias,
                mysh->alias[i]->real_command);
                return (0);
        }
    }
    for (int i = 0; builtin[i].name != 0; i++) {
        if (strcmp(command_line, builtin[i].name) == 0) {
            printf("%s: shell built-in command.\n", command_line);
            return (0);
        }
    }
    return (which_check_path(command_line, mysh));
}

int build_in_which(char **command_line, minishell *mysh)
{
    int temp = 0;
    int temp2 = 0;
    int check = 0;

    for (int k = 0; command_line[k] != NULL; k++)
        check++;
    if (check == 1) {
        printf("which: Too few arguments.\n");
        return (temp2);
    }
    for (int i = 1; command_line[i] != NULL; i++) {
        temp = main_if_which(command_line[i], mysh);
        if (temp == 1)
            temp2 = 1;
    }
    return (temp2);
}
