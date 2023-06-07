/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** alias
*/
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static int print_alias(t_alias **alias)
{
    for (int i = 0; alias[i] != NULL; i++)
        printf("%s\t%s\n", alias[i]->alias, alias[i]->real_command);
    return (0);
}

static int get_arr_size_with_str(char **arr, int start)
{
    int size = 0;

    for (int i = start; arr[i] != NULL; i++) {
        for (int j = 0; arr[i][j] != '\0'; j++)
            size++;
        size++;
    }
    return (size);
}

static char *recreate_real_command(char **command_line)
{
    char *real_command = malloc(sizeof(char) * (get_arr_size_with_str(
        command_line, 2) + 1));
    if (real_command == NULL)
        printf("is in the recreate_real_command\n");
    strcpy(real_command, command_line[2]);
    for (int i = 3; command_line[i] != NULL; i++) {
        strcat(real_command, " ");
        strcat(real_command, command_line[i]);
    }
    return (real_command);
}

int build_in_alias(char **command_line, minishell *mysh)
{
    char *real_command = NULL;

    if (command_line[1] == NULL)
        return (print_alias(mysh->alias));
    real_command = recreate_real_command(command_line);
    for (int i = 0; mysh->alias[i] != NULL; i++) {
        if (strcmp(mysh->alias[i]->alias, command_line[1]) == 0) {
            mysh->alias[i]->real_command = strdup(real_command);
            verification_malloc(mysh->alias[i]->real_command);
            free(real_command);
            return (0);
        }
    }
    fill_alias(mysh, real_command, command_line[1]);
    return (0);
}
