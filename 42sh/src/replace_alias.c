/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** replace_alias
*/
#include <string.h>
#include <stdlib.h>
#include "minishell.h"

static char *do_if_alias(char **command_line, char *alias)
{
    char *new_command_line = malloc(sizeof(char) * (strlen(alias) + 1));

    if (new_command_line == NULL)
        printf("is in the do_if_alias\n");
    strcpy(new_command_line, alias);
    for (int i = 1; command_line[i] != NULL; i++) {
        new_command_line = realloc(new_command_line, sizeof(char) * (
            strlen(command_line[i]) + strlen(new_command_line) + 1));
        if (new_command_line == NULL)
            printf("the realloc is in the do_if_alias\n");
        strcat(new_command_line, " ");
        strcat(new_command_line, command_line[i]);
    }
    return (new_command_line);
}

static char *separate_spaces(minishell *mysh, char *command)
{
    char **arr_without_spaces = separate_str(command, " \t");

    for (int i = 0; mysh->alias[i] != NULL; i++) {
        if (strcmp(arr_without_spaces[0], mysh->alias[i]->alias) == 0) {
            return (do_if_alias(arr_without_spaces,
                mysh->alias[i]->real_command));
        }
    }
    return (command);
}

static void replace_alias(char *new_str, char *temp, char *arr_with_separator)
{
    strcat(new_str, temp);
    strcat(new_str, arr_with_separator);
    free(temp);
}

char *check_for_alias(char *str, minishell *mysh)
{
    char **arr_without_separator = separate_str(str, "\n;&|<>");
    char **arr_with_separator = separate_str(str, "\t !\"#$%'()*+,-./012345678\
9:=?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}~");
    char *temp = separate_spaces(mysh, arr_without_separator[0]);
    char *new_str = malloc(sizeof(char) * (strlen(temp) + strlen(
        arr_with_separator[0]) + 1));

    verification_malloc(new_str);
    strcpy(new_str, temp);
    strcat(new_str, arr_with_separator[0]);
    free(temp);
    for (int i = 1; arr_without_separator[i] != NULL; i++) {
        temp = separate_spaces(mysh, arr_without_separator[i]);
        new_str = realloc(new_str, sizeof(char) * (strlen(new_str)
            + strlen(temp) + strlen(arr_with_separator[i]) + 1));
        verification_malloc(new_str);
        replace_alias(new_str, temp, arr_with_separator[i]);
    }
    return (new_str);
}
