/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** create_env
*/
#include <unistd.h>
#include "minishell.h"

static void create_local_var(minishell *mysh)
{
    char buff[256];
    char *cwd = getcwd(buff, 256);

    mysh->local_var = malloc(sizeof(char *) * 50);
    verification_array_malloc(mysh->local_var);
    for (int i = 0; i != 50; i++) {
        mysh->local_var[i] = malloc(sizeof(char) * 50);
        verification_malloc(mysh->local_var[i]);
    }
    mysh->local_var[0] = NULL;
    mysh->spe_var = malloc(sizeof(char *) * 50);
    verification_array_malloc(mysh->spe_var);
    mysh->spe_var[0] = strdup("_");
    if (mysh->spe_var[0] == NULL)
        exit(84);
    mysh->spe_var[1] = malloc(sizeof(char) * (strlen(cwd) + 5));
    verification_malloc(mysh->spe_var[1]);
    mysh->spe_var[1] = strcpy(mysh->spe_var[1], "cwd\t");
    mysh->spe_var[1] = strcat(mysh->spe_var[1], cwd);
}

void dup_env(char **env, minishell *mysh)
{
    int size = 0;

    while (env[size] != NULL)
        size++;
    mysh->env = malloc(sizeof(char *) * (size + 1));
    verification_array_malloc(mysh->env);
    for (int i = 0; env[i] != NULL; i++) {
        mysh->env[i] = malloc(sizeof(char) * (strlen(env[i]) + 1));
        verification_malloc(mysh->env[i]);
    }
    for (int i = 0; env[i] != NULL; i++)
        strcpy(mysh->env[i], env[i]);
    create_local_var(mysh);
}
