/*
** EPITECH PROJECT, 2023
** unset.c
** File description:
** unset
*/
#include <stdlib.h>
#include "minishell.h"

char **create_new_unset(char *command_line, minishell *mysh, int size)
{
    char **env = malloc(sizeof(char *) * (size - 1));
    if (env == NULL)
        exit(84);
    int j = 0;

    for (int i = 0; mysh->local_var[i] != NULL; i++) {
        if (strncmp(command_line,mysh->local_var[i],strlen(command_line)) == 0)
            i++;
        if (mysh->local_var[i] == NULL) {
            env[j] = NULL;
            return (env);
        }
        env[j] = strdup(mysh->local_var[i]);
        verification_malloc(env[j]);
        j++;
    }
    env[j] = NULL;
    return (env);
}

int build_in_unset(char **command_line, minishell *mysh)
{
    int size = 0;
    int is_here = 0;

    while (command_line[size] != NULL)
        size++;
    if (size < 2) {
        printf("unsetenv: Too few arguments.\n");
        return (84);
    }
    size = 0;
    while (mysh->local_var[size] != NULL) {
        if (strncmp(command_line[1], mysh->local_var[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 0)
        return (0);
    mysh->local_var = create_new_unset(command_line[1], mysh, size);
    return (0);
}
