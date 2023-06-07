/*
** EPITECH PROJECT, 2023
** main.c
** File description:
** main
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

t_alias *create_single_alias(char *alias_name, char *real_command)
{
    t_alias *alias = malloc(sizeof(t_alias));

    if (alias == NULL)
        exit(84);
    alias->alias = strdup(alias_name);
    if (alias->alias == NULL)
        exit(84);
    alias->real_command = strdup(real_command);
    if (alias->real_command == NULL)
        exit(84);
    return (alias);
}

static t_alias **create_alias_on_start(void)
{
    t_alias **alias = malloc(sizeof(t_alias *) * 1);

    if (alias == NULL)
        exit(84);
    alias[0] = NULL;
    return (alias);
}

static void verif_malloc(minishell *mysh, char *buff, char **temp2,
    char **temp3)
{
    mysh->spe_var[3] = NULL;
    mysh->current_fold = strdup(getcwd(buff, 256));
    verification_malloc(mysh->current_fold);
    if (temp2 != NULL) {
        mysh->host = strdup(temp2[0]);
        verification_malloc(mysh->host);
        free_double_array(temp2);
    } else
        mysh->host = NULL;
    if (temp3 != NULL) {
        mysh->user = strdup(temp3[0]);
        verification_malloc(mysh->user);
        free_double_array(temp3);
    } else
        mysh->user = NULL;
}

static void get_term_type(minishell *mysh)
{
    char **temp = get_path(mysh->env, "TERM=");
    char **temp2 = get_path(mysh->env, "HOSTNAME=");
    char **temp3 = get_path(mysh->env, "USER=");
    char buff[256];

    if (temp != NULL) {
        mysh->spe_var[2] = malloc(sizeof(char) * (strlen("term\t")
            + strlen(temp[0]) + 1));
        verification_malloc(mysh->spe_var[2]);
        mysh->spe_var[2] = strcpy(mysh->spe_var[2], "term\t");
        mysh->spe_var[2] = strcat(mysh->spe_var[2], temp[0]);
        free_double_array(temp);
    } else
        mysh->spe_var[2] = NULL;
    verif_malloc(mysh, buff, temp2, temp3);
}

int main(int ac, char **av, char **env)
{
    minishell *mysh = malloc(sizeof(minishell));
    if (mysh == NULL)
        exit(84);

    (void)ac;
    (void)av;
    mysh->last_folder = NULL;
    dup_env(env, mysh);
    get_term_type(mysh);
    mysh->alias = create_alias_on_start();
    mysh->history = malloc(sizeof(t_history *) * 1);
    if (mysh->history == NULL)
        exit(84);
    mysh->history[0] = NULL;
    mysh->history_size = 0;
    mysh->exit_value = -1;
    return (start_shell(mysh));
}
