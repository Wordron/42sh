/*
** EPITECH PROJECT, 2023
** unsetenv.c
** File description:
** unsetenv
*/
#include <stdlib.h>
#include "minishell.h"

static void main_loop_unsetenv(minishell *mysh, char *command_line,
    char **env)
{
    int j = 0;

    for (int i = 0; mysh->env[i] != NULL; i++) {
        if (mysh->env[i] == NULL)
            env[j] = NULL;
        if (strncmp(command_line, mysh->env[i],
            strlen(command_line)) != 0) {
            env[j] = strdup(mysh->env[i]);
            verification_malloc(env[j]);
            j++;
        }
    }
    env[j] = NULL;
}

static void create_new_unsetenv(char *command_line, minishell *mysh,
    int size)
{
    char **env = malloc(sizeof(char *) * size);

    if (env == NULL)
        exit(84);
    main_loop_unsetenv(mysh, command_line, env);
    free_double_array(mysh->env);
    mysh->env = env;
}

int build_in_unsetenv(char **command_line, minishell *mysh)
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
    while (mysh->env[size] != NULL) {
        if (strncmp(command_line[1], mysh->env[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 0)
        return (0);
    create_new_unsetenv(command_line[1], mysh, size);
    return (0);
}
