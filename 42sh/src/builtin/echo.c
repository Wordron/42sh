/*
** EPITECH PROJECT, 2023
** echo.c
** File description:
** echo
*/
#include <unistd.h>
#include "minishell.h"

int build_in_echo(char **command_line, minishell *mysh)
{
    if (strcmp(command_line[1], "$?") == 0) {
        printf("%i\n", mysh->last_status);
        return (0);
    }
    for (int i = 1; command_line[i] != NULL; i++)
        printf("%s\n", command_line[i]);
    return (0);
}
