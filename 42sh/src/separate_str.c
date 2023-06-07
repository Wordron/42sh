/*
** EPITECH PROJECT, 2023
** separate_str.c
** File description:
** separate_str.c
*/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/minishell.h"

static int check_next_char(char next, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (next == delim[i])
            return (1);
    }
    return (0);
}

static int check_current_char(char current, char next, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (current == delim[i] && check_next_char(next, delim) == 0)
            return (1);
    }
    return (0);
}

static int count_size(char *str, char *delim)
{
    int size = 2;

    for (int i = 0; str[i + 1] != '\0'; i++)
        size = size + check_current_char(str[i], str[i + 1], delim);
    return (size);
}

char **separate_str(char *argv, char *delim)
{
    int i = 0;
    char *temp = NULL;
    int size = count_size(argv, delim);
    char *str = malloc(sizeof(char) * (strlen(argv) + 1));
    char **final = malloc(sizeof(char *) * (size + 1));
    verification_malloc(str);
    verification_array_malloc(final);
    for (int j = 0; j != size; j++) {
        final[j] = malloc(sizeof(char) * 999);
        verification_malloc(final[j]);
    }
    for (strcpy(str, argv); ; str = NULL) {
        temp = strtok(str, delim);
        if (temp == NULL) {
            final[i] = NULL;
            return (final);
        }
        strcpy(final[i], temp);
        i++;
    }
}
