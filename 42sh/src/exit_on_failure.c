/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exit_on_failure
*/
#include <stdlib.h>

void verification_malloc(char *str)
{
    if (str == NULL)
        exit(84);
}

void verification_array_malloc(char **str)
{
    if (str == NULL)
        exit(84);
}
