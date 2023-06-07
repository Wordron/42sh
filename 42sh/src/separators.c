/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** separators
*/
#include "minishell.h"

static char *replace_double_pipes(char *str)
{
    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (str[i] == '|' && str[i + 1] == '|') {
            str[i] = '~';
            str[i + 1] = '~';
        }
    }
    return (str);
}

static int separate_logic_separators(char *str, minishell *mysh)
{
    replace_double_pipes(str);
    char delim[104] = "\t <>!\"#$%'()*+,-.|/0123456789:=?@ABCDEFGHIJKLM \
        NOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{}\n;";
    char **separators = separate_str(str, delim);
    char **command_args = separate_str(str, "&~");

    distribute_separators(mysh, separators, command_args);
    free_double_array(command_args);
    free_double_array(separators);
    return (0);
}

int set_command(char *str, minishell *mysh)
{
    char **arr = separate_str(str, "\n;");

    for (int i = 0; arr[i] != NULL; i++)
        separate_logic_separators(arr[i], mysh);
    free_double_array(arr);
    return (0);
}
