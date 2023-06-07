/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** send_command_line
*/
#include "minishell.h"

static void free_path(char **path)
{
    if (path != NULL)
        free_double_array(path);
    return;
}

static int redirect_command(char **command_line, minishell *mysh)
{
    mysh->path = get_path(mysh->env, "PATH=:");
    for (int i = 0; builtin[i].name != 0; i++) {
        if (strcmp(command_line[0], builtin[i].name) == 0) {
            forking_for_builtins(command_line, mysh, i);
            free_path(mysh->path);
            return (0);
        }
    }
    if (mysh->path == NULL) {
        command_slash(command_line, mysh);
        return (0);
    }
    command_path(command_line, mysh);
    free_path(mysh->path);
    return (0);
}

void send_command_line(char *command, minishell *mysh)
{
    char **command_line = separate_str(command, " \t");

    if (command_line[0] == NULL)
        return;
    if (test_slashes(command_line[0]) == 1)
        command_slash(command_line, mysh);
    else
        redirect_command(command_line, mysh);
}
