/*
** EPITECH PROJECT, 2023
** where.c
** File description:
** where
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

static int is_access(char *command_line, char *temp_path)
{
    if (access(command_line, F_OK) == 0) {
        printf("%s\n", command_line);
        free(temp_path);
        return (0);
    }
    return (1);
}

static int where_check_path(char *command_line, minishell *mysh)
{
    char *command = NULL;
    char *temp_path = NULL;
    char *cmd = strdup(command_line);
    int is_found = 1;
    if (cmd == NULL)
        exit(84);
    for (int i = 0; mysh->path[i] != NULL; i++) {
        if ((temp_path = strdup(mysh->path[i])) == NULL)
            exit(84);
        command = strcat(strcat(temp_path, "/"), cmd);
        strcpy(command_line, command);
        if (is_access(command_line, temp_path) == 0)
            is_found = 0;
        temp_path = NULL;
        command = NULL;
    }
    free(cmd);
    free(temp_path);
    return (is_found);
}

static int main_if_where(char *command_line, minishell *mysh)
{
    unsigned int return_value = 0;

    for (int i = 0; mysh->alias[i] != NULL; i++) {
        if (strcmp(mysh->alias[i]->alias, command_line) == 0) {
            printf("%s is aliased to %s\n", mysh->alias[i]->alias,
                mysh->alias[i]->real_command);
            return_value++;
        }
    }
    for (int i = 0; builtin[i].name != 0; i++) {
        if (strcmp(command_line, builtin[i].name) == 0) {
            printf("%s is a shell built-in\n", command_line);
            return_value++;
        }
    }
    if (where_check_path(command_line, mysh) == 0)
        return_value++;
    if (return_value == 0)
        return (1);
    return (0);
}

int build_in_where(char **command_line, minishell *mysh)
{
    int temp = 0;
    int temp2 = 0;
    int check = 0;

    for (int k = 0; command_line[k] != NULL; k++)
        check++;
    if (check == 1) {
        printf("where: Too few arguments.\n");
        return (temp2);
    }
    for (int i = 1; command_line[i] != NULL; i++) {
        temp = main_if_where(command_line[i], mysh);
        if (temp == 1)
            temp2 = 1;
    }
    return (temp2);
}
