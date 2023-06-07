/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** history
*/
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "minishell.h"

static void fill_history(minishell *mysh, char *str)
{
    time_t now = time(NULL);
    struct tm *time = localtime(&now);

    mysh->history[mysh->history_size - 1]->command = strdup(str);
    verification_malloc(mysh->history[mysh->history_size - 1]->command);
    mysh->history[mysh->history_size - 1]->min = time->tm_min;
    mysh->history[mysh->history_size - 1]->hour = time->tm_hour;
    mysh->history[mysh->history_size] = NULL;
}

void update_history(minishell *mysh, char *str)
{
    char *temp = strdup(str);

    if (temp == NULL)
        exit(84);
    str = strtok(temp, "\n");
    if (mysh->history_size > 0 && strcmp(
        mysh->history[mysh->history_size - 1]->command, str) == 0)
        return;
    mysh->history_size++;
    mysh->history = realloc(mysh->history, sizeof(t_history *) * (
        mysh->history_size + 1));
    if (mysh->history == NULL)
        exit(84);
    mysh->history[mysh->history_size - 1] = malloc(sizeof(t_history));
    if (mysh->history[mysh->history_size - 1] == NULL)
        exit(84);
    fill_history(mysh, str);
    free(temp);
}

static int print_history(t_history **history, int start)
{
    for (int i = start; history[i] != NULL; i++)
        printf("%5.i  %i:%i\t%s\n", i + 1, history[i]->hour,
            history[i]->min, history[i]->command);
    return (0);
}

static void reset_history(minishell *mysh)
{
    for (int i = 0; mysh->history[i] != NULL; i++) {
        free(mysh->history[i]->command);
        free(mysh->history[i]);
    }
    free(mysh->history);
    mysh->history = malloc(sizeof(t_history *) * 1);
    if (mysh->history == NULL)
        printf("is in the reset_history");
    mysh->history[0] = NULL;
    mysh->history_size = 0;
}

int build_in_history(char **command_line, minishell *mysh)
{
    int size = 0;
    int start = 0;

    if (command_line[1] == NULL)
        return (print_history(mysh->history, 0));
    while (command_line[size] != NULL)
        size++;
    if (size > 2) {
        printf("history: Too many arguments.");
        return (1);
    }
    if (my_str_isnum(command_line[1]) == 1) {
        start = mysh->history_size - atoi(command_line[1]);
        if (start < 0)
            start = 0;
        return (print_history(mysh->history, start));
    }
    if (strcmp(command_line[1], "-c") == 0)
        reset_history(mysh);
    return (0);
}
