/*
** EPITECH PROJECT, 2023
** start_shell.c
** File description:
** start_shell
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include "minishell.h"

static int check_for_cher_in_str(char to_find, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find)
            return (1);
    }
    return (0);
}

static void send_for_replacement(char *str, minishell *mysh)
{
    int temp = check_for_cher_in_str('!', str);
    int str_validity = check_str_validity(str);

    if (str_validity == 0) {
        if (mysh->history_size != 0)
            str = replace_by_history(str, mysh);
        if (mysh->history_size != 0 && temp == 1 && str != NULL)
            printf("%s", str);
        if (str != NULL) {
            update_history(mysh, str);
            str = check_for_alias(str, mysh);
            set_command(str, mysh);
        }
        return;
    }
    if (str_validity == 1)
        mysh->last_status = 1;
    if (str_validity == 2)
        mysh->last_status = 0;
}

static void do_exit(minishell *mysh)
{
    if (mysh->exit_value == 0)
        exit(mysh->last_status);
    exit(mysh->exit_value);
}

int start_shell(minishell *mysh)
{
    char *str = NULL;
    char *prompt = malloc(sizeof(char) * 200);
    if (prompt == NULL)
        exit(84);
    size_t len = 0;

    while (1) {
        str = NULL;
        len = 0;
        prompt = get_prompt(mysh);
        if (isatty(0) == 1)
            printf("%s", prompt);
        if (getline(&str, &len, stdin) == -1) {
            printf("\n");
            exit(mysh->last_status);
        }
        send_for_replacement(str, mysh);
        if (mysh->exit_value != -1)
            do_exit(mysh);
    }
}
