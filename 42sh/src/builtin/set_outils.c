/*
** EPITECH PROJECT, 2023
** set_outils.c
** File description:
** set_outils
*/
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int get_size(char **command_line)
{
    int size = 0;

    while (command_line[size] != NULL)
        size++;
    return (size);
}

int check_if_too_many_args(int size, char **command_line, minishell *mysh)
{
    if (size > 4) {
        printf("set: Variable name must begin with a letter.\n");
        return (84);
    }
    if (size == 1)
        return (build_in_env_local(command_line, mysh));
    return (0);
}

int check_if_no_spaces(char **command_line)
{
    int check = 0;

    for (int i = 0; i != (int) strlen(command_line[1]) - 1; i++) {
        if (command_line[1][i] == '=' && (strlen(command_line[1]) - 1) != 1)
            check = 1;
    }
    return (check);
}

int do_if_spaces(char **command_line, minishell *mysh, int size)
{
    if (size == 4)
        return (set_with_value1(command_line, mysh));
    else
        return (set_with_null1(command_line, mysh));
}

int check_char_set(char *var_name)
{
    if ((var_name[0] < 'A' || var_name[0] > 'Z') &&
        (var_name[0] < 'a' || var_name[0] > 'z')) {
        printf("set: Variable name must begin with a letter.\n");
        return (84);
    }
    for (int i = 0; var_name[i] != '\0'; i++) {
        if ((var_name[i] < '0' || var_name[i] > '9') &&
            (var_name[i] < 'A' || var_name[i] > 'Z') &&
            (var_name[i] < 'a' || var_name[i] > 'z') &&
            var_name[i] != '_' && var_name[i] != '.') {
            printf("set: Variable name must contain ");
            printf("alphanumeric characters.\n");
            return (84);
        }
    }
    return (0);
}
