/*
** EPITECH PROJECT, 2023
** builtins.c
** File description:
** builtins
*/
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

int build_in_builtins(char **command_line, minishell *mysh)
{
    (void)command_line;
    (void)mysh;
    for (int i = 0; builtin[i].name != 0; i++)
        printf("%s : %s\n", builtin[i].name, builtin[i].man);
    return (0);
}
