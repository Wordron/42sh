/*
** EPITECH PROJECT, 2023
** builtin_array.c
** File description:
** builtin_array
*/
#include "minishell.h"

const t_builtin builtin[] = {
    {"alias", "create an alias for a command", build_in_alias},
    {"cd", "change the directory", build_in_cd},
    {"chdir", "change the directory", build_in_cd},
    {"exit", "exit the shell", build_in_exit},
    {"builtins", "print the list of builtins and their man",
        build_in_builtins},
    {"echo", "print it's parameters", build_in_echo},
    {"env", "print the current environnement", build_in_env},
    {"local_env", "print the current local var env", build_in_env_local},
    {"setenv", "add or overwrite a variable on the environnement",
        build_in_setenv},
    {"unsetenv", "remove a variable from the environnement",
        build_in_unsetenv},
    {"where", "show all the occurence of the wanted command in PATH",
        build_in_where},
    {"which", "show the first occurence of the wanted command in PATH",
        build_in_which},
    {"set", "add or overwrite a variable on the locale variables",
        build_in_set},
    {"unset", "remove a variable from the locale variables",
        build_in_unset},
    {"history", "display the command history", build_in_history},
    {0, 0, 0},
};
