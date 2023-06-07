/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** fill_alias
*/
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static int alias_struct_size(t_alias **alias)
{
    int i = 0;

    while (alias[i] != NULL)
        i++;
    return (i);
}

void fill_alias(minishell *mysh, char *real_command, char *command_line)
{
    int size_of_alias_struct = alias_struct_size(mysh->alias);

    mysh->alias = realloc(mysh->alias, sizeof(t_alias *) * (
        size_of_alias_struct + 2));
    if (mysh->alias == NULL)
        exit(84);
    mysh->alias[size_of_alias_struct] = create_single_alias(
        command_line, real_command);
    mysh->alias[size_of_alias_struct + 1] = NULL;
    free(real_command);
}
