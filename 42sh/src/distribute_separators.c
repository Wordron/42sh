/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** separators
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "minishell.h"

static int check_in_between_separators(char *command, int start, int end)
{
    if (end - start < 2)
        return (0);
    for (int i = start; i < end; i++) {
        if (command[i] != '&' && command[i] != '~' && command[i] != ';'
            && command[i] != ' ' && command[i] != '\t')
            return (0);
    }
    return (1);
}

int check_separators_validity(char *command)
{
    int start = 0;
    int temp = 0;

    for (int i = 0; command[i] != '\0'; i++ ) {
        if (command[i] == '&' || command[i] == '~' || command[i] == ';') {
            temp = check_in_between_separators(command, start, i);
            start = i;
        }
        if (temp == 1) {
            printf("Invalid null command.\n");
            return (84);
        }
    }
    return (0);
}

static int print_error_message(minishell *mysh, char **separators,
    char **command_args, int i)
{
    if (strlen(separators[i]) == 2 && separators[i][0] == '~'
        && separators[i][1] == '~' && command_args[i + 1] != NULL) {
        get_redirections(command_args[i], mysh);
        if (mysh->last_status == 0)
            return (2);
        if (command_args[i + 1] != NULL)
            get_redirections(command_args[i + 1], mysh);
        return (1);
    }
    printf("Invalid null command.\n");
    return (2);
}

static int check_for_separators(minishell *mysh, char **separators,
    char **command_args, int i)
{
    if (separators[i] == NULL) {
        get_redirections(command_args[i], mysh);
        return (0);
    }
    if (strlen(separators[i]) == 2 && separators[i][0] == '&'
    && separators[i][1] == '&') {
        get_redirections(command_args[i], mysh);
        if (mysh->last_status != 0)
            return (2);
        if (command_args[i + 1] != NULL)
            get_redirections(command_args[i + 1], mysh);
        return (1);
    }
    return (print_error_message(mysh, separators, command_args, i));
}

int distribute_separators(minishell *mysh, char **separators,
    char **command_args)
{
    int temp = 0;

    for (int i = 0; command_args[i] != NULL; i = i + temp + 1) {
        temp = check_for_separators(mysh, separators, command_args, i);
        if (temp == 2)
            return (1);
    }
    return (0);
}
