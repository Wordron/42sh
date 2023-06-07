/*
** EPITECH PROJECT, 2023
** distribute_redirections
** File description:
** distribute_redirections
*/
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static void init_pipe(minishell *mysh)
{
    if (mysh->fd_in != STDIN_FILENO)
        close(mysh->fd_in);
    if (mysh->is_pipe == 1) {
        mysh->fd_in = mysh->pipefd[mysh->current_pipe][0];
        mysh->current_pipe++;
    }
}

int distribute_redirections(minishell *mysh, char **redirections,
    char **command_args)
{
    int temp = 0;

    for (int i = 0; command_args[i] != NULL; i = i + temp + 1) {
        temp = check_next_redirection(mysh, redirections[i],
            command_args[i + 1]);
        if (temp == 2) {
            temp = temp + check_next_redirection(mysh, redirections[i + 1],
            command_args[i + 2]) - 1;
        }
        if (mysh->fd_in == -1 || mysh->fd_out == -1 || temp == -1)
            return (1);
        if (mysh->is_pipe == 1 && command_args[i + 1] == NULL) {
            printf("Invalid null command.\n");
            mysh->last_status = 1;
            return (1);
        }
        send_command_line(command_args[i], mysh);
        init_pipe(mysh);
    }
    return (0);
}
