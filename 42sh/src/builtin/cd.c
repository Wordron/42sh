/*
** EPITECH PROJECT, 2023
** cd.c
** File description:
** cd
*/
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "minishell.h"

int check_folder_validity(char *folder_path)
{
    DIR *fd;

    fd = opendir(folder_path);
    if (fd == NULL)
        return (3);
    closedir(fd);
    if (access(folder_path, X_OK) != 0)
        return (2);
    if (access(folder_path, F_OK) == 0)
        return (0);
    return (1);
}

static void change_dir(char buff[256], char *directory, minishell *mysh)
{
    chdir(directory);
    mysh->last_folder = malloc(sizeof(char) * (strlen(buff) + 1));
    if (mysh->last_folder == NULL)
        printf("is in the change_dirn");
    strcpy(mysh->last_folder, buff);
    return;
}

static int go_home(minishell *mysh, char buff[256])
{
    char **home = get_path(mysh->env, "HOME=");

    if (home == NULL) {
        printf("cd: HOME not set\n");
        return (84);
    }
    change_dir(buff, home[0], mysh);
    change_spe_var_cwd(mysh);
    return (0);
}

static int redirect_chdir(minishell *mysh, char **command_line, int arg)
{
    char buff[256];

    getcwd(buff, 256);
    if (arg == 1)
        return (go_home(mysh, buff));
    if (strcmp(command_line[1], "-") == 0) {
        change_dir(buff, mysh->last_folder, mysh);
        change_spe_var_cwd(mysh);
        return (0);
    }
    if (check_folder_validity(command_line[1]) == 0) {
        change_dir(buff, command_line[1], mysh);
        change_spe_var_cwd(mysh);
        return (0);
    }
    return (error_cd(command_line[1]));
}

int build_in_cd(char **command_line, minishell *mysh)
{
    int i = 0;

    while (command_line[i] != NULL)
        i++;
    if (i > 2) {
        printf("Too many arguments\n");
        return (1);
    }
    return (redirect_chdir(mysh, command_line, i));
}
