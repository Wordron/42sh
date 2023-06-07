/*
** EPITECH PROJECT, 2023
** free_mysh.c
** File description:
** free_mysh.c
*/
#include <stdlib.h>
#include "minishell.h"

void free_double_array(char **array)
{
    for (int j = 0; array[j] != NULL; j++)
        free(array[j]);
    free(array);
}
