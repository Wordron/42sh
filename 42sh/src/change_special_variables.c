/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** change_special_variables
*/
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "minishell.h"

void change_spe_var_cwd(minishell *mysh)
{
    char buff[256];

    mysh->spe_var[1] = malloc(sizeof(char) * (strlen("cwd\t")
        + strlen(getcwd(buff, 256)) + 1));
    if (mysh->spe_var[1] == NULL)
        exit(84);
    mysh->spe_var[1] = strcpy(mysh->spe_var[1], "cwd\t");
    mysh->spe_var[1] = strcat(mysh->spe_var[1], getcwd(buff, 256));
    mysh->current_fold = strdup(getcwd(buff, 256));
    if (mysh->current_fold == NULL)
        exit(84);
}
