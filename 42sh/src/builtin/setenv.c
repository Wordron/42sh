/*
** EPITECH PROJECT, 2023
** setenv.c
** File description:
** setenv
*/
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int check_char(char *var_name)
{
    if ((var_name[0] < 'A' || var_name[0] > 'Z') &&
        (var_name[0] < 'a' || var_name[0] > 'z')) {
        printf("setenv: Variable name must begin with a letter.\n");
        return (84);
    }
    for (int i = 0; var_name[i] != '\0'; i++) {
        if ((var_name[i] < '0' || var_name[i] > '9') &&
            (var_name[i] < 'A' || var_name[i] > 'Z') &&
            (var_name[i] < 'a' || var_name[i] > 'z') &&
            var_name[i] != '_' && var_name[i] != '.') {
            printf("setenv: Variable name must contain ");
            printf("alphanumeric characters.\n");
            return (84);
        }
    }
    return (0);
}

static int set_with_null(char **command_line, minishell *mysh)
{
    int size = 0;
    int is_here = 0;

    while (mysh->env[size] != NULL) {
        if (strncmp(command_line[1], mysh->env[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 1)
        replace_setenv(mysh, command_line[1], "\0");
    else
        mysh->env = create_new_setenv(mysh, size, command_line[1], "\0");
    return (0);
}

static int set_with_value(char **command_line, minishell *mysh)
{
    int size = 0;
    int is_here = 0;

    while (mysh->env[size] != NULL) {
        if (strncmp(command_line[1], mysh->env[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 1)
        replace_setenv(mysh, command_line[1], command_line[2]);
    else
        mysh->env = create_new_setenv(mysh, size, command_line[1],
        command_line[2]);
    return (0);
}

int build_in_setenv(char **command_line, minishell *mysh)
{
    int size = 0;

    while (command_line[size] != NULL)
        size++;
    if (size < 2)
        return (build_in_env(command_line, mysh));
    else if (size > 3) {
        printf("setenv: Too many arguments.\n");
        return (84);
    }
    if (check_char(command_line[1]) == 84)
        return (84);
    if (size == 3)
        return (set_with_value(command_line, mysh));
    else
        return (set_with_null(command_line, mysh));
    return (0);
}
