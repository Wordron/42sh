/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** check_str_validity
*/
#include <string.h>
#include "minishell.h"

static int check_separators_and_redirections_with_len(char **arr, int i)
{
    if (strlen(arr[i]) < 2) {
        if ((arr[i][0] != '|' && arr[i][0] != '<' && arr[i][0] != '>'
            && arr[i][0] != '\n')) {
            printf("Invalid null command.\n");
            return (1);
        }
    }
    if (strlen(arr[i]) >= 2) {
        if ((arr[i][0] != '|' && arr[i][0] != '<' && arr[i][0] != '>'
            && arr[i][0] != '\n') || (arr[i][1] != '|' && arr[i][1] != '<'
            && arr[i][1] != '>' && arr[i][1] != '\n')) {
            printf("Invalid null command.\n");
            return (1);
        }
    }
    return (0);
}

static int check_separators_and_redirections(char **arr, int i)
{
    if (i == 0) {
        printf("Invalid null command.\n");
        return (1);
    }
    if (arr[i + 1] != NULL && (strncmp(arr[i + 1], "&", 1) == 0 ||
    strncmp(arr[i + 1], "|", 1) == 0 || strncmp(arr[i + 1], "<", 1) == 0
        || strncmp(arr[i + 1], ">", 1) == 0)) {
        printf("Ambiguous input redirect.\n");
        return (1);
    }
    return (check_separators_and_redirections_with_len(arr, i));
}

static int check_for_single_char(char **arr)
{
    if (arr[1] == NULL && (strncmp(arr[0], "\n", 1) == 0 ||
        strncmp(arr[0], ";", 1) == 0 || strncmp(arr[0], "&", 1) == 0)) {
        free_double_array(arr);
        return (2);
    }
    if (arr[1] == NULL && (strncmp(arr[0], "<", 1) == 0
        || strncmp(arr[0], ">", 1) == 0)) {
        printf("Missing name for redirect.\n");
        free_double_array(arr);
        return (1);
    }
    if (arr[1] == NULL && strncmp(arr[0], "|", 1) == 0) {
        printf("Invalid null command.\n");
        free_double_array(arr);
        return (1);
    }
    return (0);
}

int check_str_validity(char *str)
{
    char **arr = separate_str(str, " \t");
    unsigned int return_value = check_for_single_char(arr);

    if (return_value != 0)
        return (return_value);
    for (int i = 0; arr[i] != NULL; i++) {
        if (strncmp(arr[i], "|", 1) == 0 || strncmp(arr[i], "<", 1) == 0
            || strncmp(arr[i], ">", 1) == 0 || strncmp(arr[i], "\n", 1) == 0)
            return_value = check_separators_and_redirections(arr, i);
        if (return_value == 1) {
            free_double_array(arr);
            return (1);
        }
    }
    free_double_array(arr);
    return (return_value);
}
