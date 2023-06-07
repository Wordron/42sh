/*
** EPITECH PROJECT, 2023
** set.c
** File description:
** set
*/
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int set_with_null1(char **command_line, minishell *mysh)
{
    int size = 0;
    int is_here = 0;

    while (mysh->local_var[size] != NULL) {
        if (strncmp(command_line[1], mysh->local_var[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 1)
        replace_set(mysh, command_line[1], "\0");
    else
        mysh->local_var = create_new_set(mysh, size, command_line[1], "\0");
    return (0);
}

int set_with_value1(char **command_line, minishell *mysh)
{
    int size = 0;
    int is_here = 0;

    while (mysh->local_var[size] != NULL) {
        if (strncmp(command_line[1], mysh->local_var[size],
            strlen(command_line[1])) == 0)
            is_here = 1;
        size++;
    }
    if (is_here == 1)
        replace_set(mysh, command_line[1], command_line[3]);
    else
        mysh->local_var = create_new_set(mysh, size, command_line[1],
        command_line[3]);
    return (0);
}

char *get_args_if_no_spaces(char *arg)
{
    int j = 0;
    int index = 0;
    char *temp = malloc(sizeof(char) * 50);
    if (temp == NULL)
        printf("is in the get_args_if_no_spaces");
    while (arg[j] != '=')
        j++;
    for (j = j + 1; arg[j] != 0; j++) {
        temp[index] = arg[j];
        index++;
    }
    temp[index] = 0;
    return (temp);
}

char **get_all_array_command(char **command_line, int size)
{
    char **commands = malloc(sizeof(char *) * size + 2);
    if (commands == NULL)
        printf("is in the get_all_array_command");
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; i != size + 2; i++) {
        commands[i] = malloc(sizeof(char) * 50);
        if (commands[i] == NULL)
            printf("is in the get_all_array_command");
    }
    for (j = 0; command_line[j] != 0; j++)
        commands[j] = strcpy(commands[j], command_line[j]);
    for (k = 0; command_line[1][k] != '='; k++)
            commands[1][k] = command_line[1][k];
        commands[1][k] = 0;
    commands[2] = strcpy(commands[2], "\t");
    commands[3] = get_args_if_no_spaces(command_line[1]);
    return (commands);
}

int build_in_set(char **command_line, minishell *mysh)
{
    int size = get_size(command_line);
    int check = 0;
    char **commands;
    int error = check_if_too_many_args(size, command_line, mysh);

    if (error == 84)
        return (84);
    if (error == 0 && size == 1)
        return (0);
    check = check_if_no_spaces(command_line);
    if (check == 1) {
        commands = get_all_array_command(command_line, size);
        if (check_char_set(commands[1]) == 84)
            return (84);
        return (set_with_value1(commands, mysh));
    }
    if (check_char_set(command_line[1]) == 84)
        return (84);
    return (do_if_spaces(command_line, mysh, size));
    return (0);
}
