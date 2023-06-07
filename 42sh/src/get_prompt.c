/*
** EPITECH PROJECT, 2023
** get_prompt.c
** File description:
** get_prompt
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include "minishell.h"

char *get_prompt(minishell *mysh)
{
    char *prompt = malloc(sizeof(char) * 200);

    if (prompt == NULL)
        exit(84);
    if (mysh->user == NULL || mysh->host == NULL
        || mysh->current_fold == NULL) {
        strcpy(prompt, "$> ");
        return (prompt);
    }
    strcpy(prompt, "[");
    strcat(prompt, mysh->user);
    strcat(prompt, "@");
    strcat(prompt, mysh->host);
    strcat(prompt, " ");
    strcat(prompt, mysh->current_fold);
    strcat(prompt, "]$> ");
    return (prompt);
}
