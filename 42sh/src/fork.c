/*
** EPITECH PROJECT, 2023
** fork.c
** File description:
** fork
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

static int check_arg(char **command_line)
{
    int i = 0;

    while (command_line[i] != NULL)
        i++;
    return (i);
}

static int check_if_going_in_the_fork(char **command_line)
{
    if (strcmp("unsetenv", command_line[0]) == 0 ||
    (strcmp("setenv", command_line[0]) == 0 && check_arg(command_line) != 1)
    || strcmp("cd", command_line[0]) == 0
    || (strcmp("set", command_line[0]) == 0 && check_arg(command_line) != 1)
    || strcmp("unset", command_line[0]) == 0 ||
    (strcmp("alias", command_line[0]) == 0 && check_arg(command_line) != 1) ||
    (strcmp("history", command_line[0]) == 0 && check_arg(command_line) == 2 &&
        strcmp(command_line[1], "-c") == 0))
        return (0);
    return (1);
}

static int do_if_exit(int last_status, char **command_line)
{
    if (command_line[1] == NULL)
        return (last_status);
    if (my_is_num(command_line[1]) != 0 || get_arr_size(command_line) > 2) {
        printf("exit: Expression Syntax.\n");
        return (-1);
    }
    return (atoi(command_line[1]));
}

int forking_for_builtins(char **command_line, minishell *mysh, int i)
{
    int child_pid = 0;
    int temp = 0;

    if (strcmp("exit", command_line[0]) == 0)
        mysh->exit_value = do_if_exit(mysh->last_status, command_line);
    if (check_if_going_in_the_fork(command_line) == 0)
        return (builtin[i].f_builtin(command_line, mysh));
    child_pid = fork();
    mysh->nb_fork++;
    if (child_pid == 0) {
        dup2(mysh->fd_in, STDIN_FILENO);
        dup2(mysh->fd_out, STDOUT_FILENO);
        temp = builtin[i].f_builtin(command_line, mysh);
        exit(temp);
    }
    if (mysh->fd_out != STDOUT_FILENO)
        close(mysh->fd_out);
    return (0);
}

int forking(char **final, minishell *mysh)
{
    int child_pid = 0;

    child_pid = fork();
    mysh->nb_fork++;
    if (child_pid == 0) {
        dup2(mysh->fd_in, STDIN_FILENO);
        dup2(mysh->fd_out, STDOUT_FILENO);
        execve(final[0], final, mysh->env);
        exit(1);
    }
    if (mysh->fd_out != STDOUT_FILENO)
        close(mysh->fd_out);
    return (0);
}
