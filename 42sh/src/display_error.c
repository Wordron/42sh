/*
** EPITECH PROJECT, 2023
** display_error.c
** File description:
** display_error
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "minishell.h"

void display_core_dumped(int child_status)
{
    if (__WCOREDUMP(child_status))
        printf(" (core dumped)\n");
    else
        printf("\n");
}

void display_error(int sig, int child_status)
{
    if (sig == 11) {
        printf("Segmentation fault");
        display_core_dumped(child_status);
    }
    if (sig == 6) {
        printf("Abort");
        display_core_dumped(child_status);
    }
    if (sig == 8) {
        printf("Floating exception");
        display_core_dumped(child_status);
    }
}

void check_error(int child_status)
{
    int sig = 0;

    if (WIFSIGNALED(child_status)) {
        sig = WTERMSIG(child_status);
        display_error(sig, child_status);
    }
}

int error_cd(char *folder)
{
    printf("%s", folder);
    if (check_folder_validity(folder) == 3 &&
        access(folder, F_OK) == 0) {
        printf(": Not a directory.\n");
        return (1);
    }
    if (access(folder, X_OK) == -1 &&
        access(folder, F_OK) == 0) {
        printf(": Permission denied.\n");
        return (1);
    }
    printf(": No such file or directory.\n");
    return (1);
}
