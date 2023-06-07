/*
** EPITECH PROJECT, 2023
** Mini_shell_2
** File description:
** check_redirection
*/
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include <stdio.h>

int check_in_between(char *command, int start, int end)
{
    if (end - start < 2)
        return (0);
    for (int i = start; i < end; i++) {
        if (command[i] != '<' && command[i] != '|' && command[i] != '>'
            && command[i] != ' ' && command[i] != '\t')
            return (0);
    }
    return (1);
}

int check_redirection_validity(char *command)
{
    int start = 0;
    int temp = 0;

    for (int i = 0; command[i] != '\0'; i++ ) {
        if (command[i] == '<' || command[i] == '|' || command[i] == '>') {
            temp = check_in_between(command, start, i);
            start = i;
        }
        if (temp == 1) {
            printf("Missing name for redirect.\n");
            return (84);
        }
    }
    return (0);
}

static int check_redirection_from_file(minishell *mysh, char *redirection,
    char *command_args)
{
    command_args = strtok(command_args, " \t");
    if (strlen(redirection) == 2 && redirection[0] == '>'
        && redirection[1] == '>') {
        mysh->fd_out = redirect_to_file_double(command_args);
        return (1);
    }
    if (strlen(redirection) == 1 && redirection[0] == '>') {
        mysh->fd_out = redirect_to_file_single(command_args);
        return (1);
    }
    if (strlen(redirection) == 1 && redirection[0] == '<') {
        mysh->fd_in = read_from_a_file(command_args);
        return (2);
    }
    printf("%s: Redirect not found.\n", redirection);
    return (-1);
}

int check_next_redirection(minishell *mysh, char *redirection,
    char *command_args)
{
    mysh->is_pipe = 0;
    if (redirection == NULL) {
        mysh->fd_out = STDOUT_FILENO;
        return (0);
    }
    if (strlen(redirection) == 1 && redirection[0] == '|') {
        if (pipe(mysh->pipefd[mysh->current_pipe]) == -1)
            exit(84);
        mysh->is_pipe = 1;
        mysh->fd_out = mysh->pipefd[mysh->current_pipe][1];
        return (0);
    }
    if (strlen(redirection) == 2 && redirection[0] == '<'
        && redirection[1] == '<') {
        mysh->fd_in = redirect_twice(command_args);
        return (2);
    }
    return (check_redirection_from_file(mysh, redirection, command_args));
}
