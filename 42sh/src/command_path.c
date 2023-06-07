/*
** EPITECH PROJECT, 2023
** command_path.c
** File description:
** command_path
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"

void command_path(char **command_line, minishell *mysh)
{
    char *command = NULL;
    char *temp = malloc(sizeof(char) * (strlen(command_line[0]) + 1));

    if (temp == NULL)
        exit(84);
    strcpy(temp, command_line[0]);
    for (int i = 0; mysh->path[i] != NULL; i++) {
        command = NULL;
        command = strcat(strcat(mysh->path[i], "/"), temp);
        strcpy(command_line[0], command);
        if (access(command_line[0], F_OK) == 0) {
            forking(command_line, mysh);
            free_double_array(command_line);
            return;
        }
    }
    printf("%s: Command not found.\n", temp);
    mysh->last_status = 1;
    return;
}
