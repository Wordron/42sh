/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** replace_by_history
*/
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static char *get_from_history(char *str, int start, minishell *mysh)
{
    int size = my_strlen(str, ' ', start + 1);
    char *temp = malloc(sizeof(char) * (size + 1));
    if (temp == NULL)
        printf("is in the get_from_history\n");
    int k = 0;
    for (int j = start + 1; j < size && str[j] != '\n'; j++) {
        temp[k] = str[j];
        k++;
    }
    temp[k] = '\0';
    for (int i = mysh->history_size - 1; i >= 0; i = i - 1) {
        if (strncmp(temp, mysh->history[i]->command, strlen(temp)) == 0) {
            free(temp);
            return (mysh->history[i]->command);
        }
    }
    printf("%s: Event not found.\n", temp);
    mysh->last_status = 1;
    free(temp);
    return (NULL);
}

static char *complete_str_by_history(char *str, char *new_str, minishell *mysh)
{
    char *command_from_history = get_from_history(str, mysh->h_i, mysh);
    int temp = 0;

    if (command_from_history == NULL)
        return (NULL);
    temp = mysh->h_j + strlen(command_from_history);
    mysh->h_i = mysh->h_i + my_strlen(str, ' ', mysh->h_i + 1);
    new_str = realloc(new_str, sizeof(char) * (temp + (strlen(str) - mysh->h_i)
        + 1));
    if (new_str == NULL)
        printf("the realloc is in the complete_str_by_history\n");
    my_strcpy(new_str, command_from_history, mysh->h_j);
    mysh->h_j = temp;
    return (new_str);
}

static char *separate_if_history_needed(char *str, char *new_str,
    minishell *mysh)
{
    if (str[mysh->h_i] == '!')
        return (complete_str_by_history(str, new_str, mysh));
    new_str[mysh->h_j] = str[mysh->h_i];
    mysh->h_i++;
    mysh->h_j++;
    return (new_str);
}

char *replace_by_history(char *str, minishell *mysh)
{
    char *new_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (new_str == NULL)
        printf("is in the replace_by_history\n");
    mysh->h_j = 0;
    mysh->h_i = 0;
    str = my_strreplace(str, '\t', ' ');
    while (str[mysh->h_i] != '\0' && str[mysh->h_i] != '\n') {
        new_str = separate_if_history_needed(str, new_str, mysh);
        if (new_str == NULL)
            return (NULL);
    }
    new_str = realloc(new_str, sizeof(char) * (strlen(new_str) + 2));
    if (new_str == NULL)
        printf("the realloc is in the replace_by_history\n");
    new_str[mysh->h_j] = '\n';
    new_str[mysh->h_j + 1] = '\0';
    return (new_str);
}
