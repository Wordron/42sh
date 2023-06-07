/*
** EPITECH PROJECT, 2023
** exit.c
** File description:
** exit
*/
#include <stdlib.h>
#include "minishell.h"

int get_arr_size(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
        i++;
    return (i);
}

int my_is_num(char *str)
{
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] < '0' || str[i] > '9')
            return (1);
    }
    return (0);
}

int build_in_exit(char **command_line, minishell *mysh)
{
    if (command_line[1] == NULL)
        exit(mysh->last_status);
    if (my_is_num(command_line[1]) != 0 || get_arr_size(command_line) > 2) {
        printf("exit: Expression Syntax.\n");
        return (1);
    }
    exit(atoi(command_line[1]));
}
