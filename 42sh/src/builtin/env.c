/*
** EPITECH PROJECT, 2023
** env.c
** File description:
** env
*/
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int build_in_env(char **command_line, minishell *mysh)
{
    (void)command_line;
    for (int i = 0; mysh->env[i] != NULL; i++)
        printf("%s\n", mysh->env[i]);
    return (0);
}

int build_in_env_local(char **command_line, minishell *mysh)
{
    (void)command_line;
    for (int i = 0; mysh->local_var[i] != NULL; i++)
        printf("%s\n", mysh->local_var[i]);
    for (int i = 0; mysh->spe_var[i] != NULL; i++)
        printf("%s\n", mysh->spe_var[i]);
    return (0);
}
