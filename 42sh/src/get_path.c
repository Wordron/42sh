/*
** EPITECH PROJECT, 2023
** get_path.c
** File description:
** get_path
*/
#include <stdlib.h>
#include "minishell.h"

char **get_path(char **env, char *str)
{
    char *temp;
    char **path;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], str, strlen(str) - 1) == 0) {
            temp = strdup(env[i]);
            verification_malloc(temp);
            path = separate_str(temp, str);
            free(temp);
            return (path);
        }
    }
    return (NULL);
}
