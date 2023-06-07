/*
** EPITECH PROJECT, 2023
** Mini_shell_2
** File description:
** get_redirection
*/
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

static void get_pipe(char *command, minishell *mysh)
{
    mysh->total_pipe = 0;
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '|')
            mysh->total_pipe++;
    }
    mysh->pipefd = malloc(sizeof(int *) * mysh->total_pipe);
    if (mysh->pipefd == NULL)
        printf("the malloc is in the get_pipe\n");
    for (int i = 0; i < mysh->total_pipe; i++) {
        mysh->pipefd[i] = malloc(sizeof(int) * 2);
        if (mysh->pipefd[i] == NULL)
            printf("the malloc is in the get_pipe loop\n");
    }
    return;
}

static void init_struct(char *command, minishell *mysh)
{
    get_pipe(command, mysh);
    mysh->nb_fork = 0;
    mysh->current_pipe = 0;
    mysh->fd_in = STDIN_FILENO;
    mysh->fd_out = STDOUT_FILENO;
}

static void close_curtain(minishell *mysh, char **redirections,
    char **command_args)
{
    int child_status = 0;

    for (int i = 0; i < mysh->nb_fork; i++) {
        waitpid(-1, &child_status, 0);
        mysh->last_status = child_status;
        check_error(child_status);
    }
    free_double_array(command_args);
    free_double_array(redirections);
    return;
}

int get_redirections(char *command, minishell *mysh)
{
    if (check_redirection_validity(command) == 84)
        return (1);
    char delim[104] = "\t !\"#$%&'()*+,-./0123456789:=?@ABCDEFGHIJKLM \
        NOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}~";
    char **redirections = separate_str(command, delim);
    char **command_args = separate_str(command, "<|>");

    init_struct(command, mysh);
    distribute_redirections(mysh, redirections, command_args);
    close_curtain(mysh, redirections, command_args);
    return (0);
}
