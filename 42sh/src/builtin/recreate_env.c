/*
** EPITECH PROJECT, 2023
** recreate_env.c
** File description:
** recreate_env
*/
#include <stdlib.h>
#include "minishell.h"

void replace_setenv(minishell *mysh, char *var_name, char *value)
{
    char *temp = NULL;

    for (int i = 0; mysh->env[i] != NULL; i++) {
        if (strncmp(var_name, mysh->env[i],
            strlen(var_name)) == 0) {
            free(mysh->env[i]);
            mysh->env[i] = malloc(sizeof(char) * (sizeof(var_name) +
                sizeof(value) + 1));
            verification_malloc(mysh->env[i]);
            temp = strcat(strcat(var_name, "="), value);
            strcpy(mysh->env[i], temp);
            return;
        }
    }
}

char **create_new_setenv(minishell *mysh, int size, char *var_name,
    char *value)
{
    char **env = malloc(sizeof(char *) * (size + 1));
    verification_array_malloc(env);
    char *temp = malloc(sizeof(char) * (strlen(var_name) + strlen(value) + 2));
    verification_malloc(temp);
    int i = 0;

    for (; mysh->env[i] != NULL; i++) {
        env[i] = strdup(mysh->env[i]);
        verification_malloc(env[i]);
    }
    strcpy(temp, var_name);
    strcat(temp, "=");
    strcat(temp, value);
    env[i] = strdup(temp);
    verification_malloc(env[i]);
    env[i + 1] = NULL;
    return (env);
}

void replace_set(minishell *mysh, char *var_name, char *value)
{
    char *temp = NULL;

    for (int i = 0; mysh->local_var[i] != NULL; i++) {
        if (strncmp(var_name, mysh->local_var[i],
            strlen(var_name)) == 0) {
            free(mysh->local_var[i]);
            mysh->local_var[i] = malloc(sizeof(char) * (sizeof(var_name) +
                sizeof(value) + 1));
            verification_malloc(mysh->local_var[i]);
            temp = strcat(strcat(var_name, "\t"), value);
            strcpy(mysh->local_var[i], temp);
            return;
        }
    }
}

char **create_new_set(minishell *mysh, int size, char *var_name,
    char *value)
{
    char **env = malloc(sizeof(char *) * (size + 1));
    if (env == NULL)
        exit(84);
    char *temp = NULL;
    int i = 0;

    for (; mysh->local_var[i] != NULL; i++) {
        env[i] = malloc(sizeof(char) * (strlen(mysh->local_var[i]) + 1));
        verification_malloc(env[i]);
    }
    env[i] = malloc(sizeof(char) * (sizeof(var_name) +
    sizeof(value) + 1));
    verification_malloc(env[i]);
    i = 0;
    for (; mysh->local_var[i] != NULL; i++)
        strcpy(env[i], mysh->local_var[i]);
    temp = strcat(strcat(var_name, "\t"), value);
    strcpy(env[i], temp);
    env[i + 1] = NULL;
    return (env);
}
