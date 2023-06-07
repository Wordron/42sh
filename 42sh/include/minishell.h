/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** minishell
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef MINISHELL_H_
    #define MINISHELL_H_

    typedef struct s_alias {
        char *alias;
        char *real_command;
    } t_alias;

    typedef struct s_history {
        char *command;
        int hour;
        int min;
    } t_history;

    typedef struct minishell {
        int **pipefd;
        int current_pipe;
        int total_pipe;
        int is_pipe;
        int fd_in;
        int fd_out;
        int nb_fork;
        int last_status;
        char *last_folder;
        char *current_fold;
        char *host;
        char *user;
        char **path;
        char **env;
        char **local_var;
        char **spe_var;
        t_alias **alias;
        t_history **history;
        int history_size;
        unsigned int h_i;
        unsigned int h_j;
        int exit_value;
    } minishell;

    typedef struct s_builtin {
        char *name;
        char *man;
        int (*f_builtin)(char **, minishell *);
    } t_builtin;

    int start_shell(minishell *mysh);
    char **get_path(char **env, char *str);
    char **separate_str(char *argv, char *delim);
    int forking(char **final, minishell *mysh);
    void check_error(int child_status);
    int error_cd(char *folder);
    int check_folder_validity(char *folder_path);
    void free_double_array(char **array);

    int forking_for_builtins(char **command_line, minishell *mysh, int i);
    void command_path(char **command_line, minishell *mysh);
    void command_slash(char **command_line, minishell *mysh);
    int test_slashes(char *command_line);
    // exit builtin command
    int build_in_exit(char **command_line, minishell *mysh);
    // cd builtin command
    int build_in_cd(char **command_line, minishell *mysh);
    // builtins builtin command
    int build_in_builtins(char **command_line, minishell *mysh);
    // echo builtin command
    int build_in_echo(char **command_line, minishell *mysh);
    // where builtin command
    int build_in_where(char **command_line, minishell *mysh);
    // which builtin command
    int build_in_which(char **command_line, minishell *mysh);
    // env builtin command
    int build_in_env(char **command_line, minishell *mysh);
    // unsetenv builtin command
    int build_in_unsetenv(char **command_line, minishell *mysh);
    // setenv builtin command
    int build_in_unset(char **command_line, minishell *mysh);
    int build_in_setenv(char **command_line, minishell *mysh);
    int build_in_set(char **command_line, minishell *mysh);
    int build_in_env_local(char **command_line, minishell *mysh);
    char **create_new_setenv(minishell *mysh, int size, char *var_name,
        char *value);
    char **create_new_set(minishell *mysh, int size, char *var_name,
    char *value);
    void replace_setenv(minishell *mysh, char *var_name, char *value);
    void replace_set(minishell *mysh, char *var_name, char *value);
    int check_char(char *var_name);
    int build_in_alias(char **command_line, minishell *mysh);
    int build_in_history(char **command_line, minishell *mysh);

    // array containing the different builtins
    extern const t_builtin builtin[];

    int check_redirection_validity(char *command);
    int set_command(char *str, minishell *mysh);
    int check_next_redirection(minishell *mysh, char *redirection,
        char *command_args);
    int distribute_redirections(minishell *mysh, char **redirections,
        char **command_args);
    void send_command_line(char *command, minishell *mysh);

    int redirect_to_file_single(char *filepath);
    int redirect_to_file_double(char *filepath);
    int read_from_a_file(char *filepath);
    int redirect_twice(char *end);
    int get_size(char **command_line);
    int check_if_too_many_args(int size, char **command_line, minishell *mysh);
    int check_if_no_spaces(char **command_line);
    int do_if_spaces(char **command_line, minishell *mysh, int size);
    int set_with_null1(char **command_line, minishell *mysh);
    int set_with_value1(char **command_line, minishell *mysh);
    int check_char_set(char *var_name);

    char *check_for_alias(char *str, minishell *mysh);
    t_alias *create_single_alias(char *alias_name, char *real_command);

    int get_redirections(char *command, minishell *mysh);
    int check_separators_validity(char *command);
    int distribute_separators(minishell *mysh, char **redirections,
        char **command_args);

    char *replace_by_history(char *str, minishell *mysh);
    void update_history(minishell *mysh, char *str);

    char *my_strreplace(char *str, char to_be_replaced, char replace);
    int my_strlen(char *str, char end, int start);
    char *my_strcpy(char *dest, char *src, int i);
    int my_str_isnum(char const *str);
    char *get_prompt(minishell *mysh);
    void change_spe_var_cwd(minishell *mysh);
    int check_str_validity(char *str);
    int verification_malloc(char *str);
    int verification_array_malloc(char **str);
    void dup_env(char **env, minishell *mysh);
    void fill_alias(minishell *mysh, char *real_command, char *command_line);
    int my_is_num(char *str);
    int get_arr_size(char **arr);


#endif /* !MINISHELL_H_ */
