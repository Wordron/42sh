##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC    =	src/main.c	\
			src/separate_str.c	\
			src/command_path.c	\
			src/command_slash.c	\
			src/free_mysh.c	\
			src/get_path.c	\
			src/fork.c	\
			src/display_error.c	\
			src/start_shell.c	\
			src/utiliti_functions.c	\
			src/send_command_line.c	\
			src/distribute_separators.c	\
			src/change_special_variables.c	\
			src/builtin/exit.c	\
			src/builtin/env.c	\
			src/builtin/cd.c	\
			src/builtin/unsetenv.c	\
			src/builtin/unset.c	\
			src/builtin/setenv.c	\
			src/builtin/set.c	\
			src/builtin/set_outils.c	\
			src/builtin/recreate_env.c	\
			src/builtin/echo.c	\
			src/builtin/builtins.c	\
			src/builtin/where.c	\
			src/builtin/which.c	\
			src/builtin/alias.c	\
			src/builtin/history.c	\
			include/builtin_array.c	\
			src/check_redirection.c	\
			src/get_redirection.c	\
			src/output_redirections.c	\
			src/input_redirections.c	\
			src/distribute_redirections.c	\
			src/replace_alias.c	\
			src/replace_by_history.c	\
			src/separators.c	\
			src/get_prompt.c	\
			src/check_str_validity.c	\
			src/exit_on_failure.c	\
			src/create_env.c	\
			src/builtin/fill_alias.c	\

OBJ    =    $(SRC:.c=.o)

NAME	=	42sh

CFLAGS = -Wall -Wshadow -Wextra -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm $(OBJ)

fclean: clean
		rm -f $(NAME)

re:		fclean all

git:
	echo -e "*.a\n*.o\n*#*#*\n#*\n.#*\n*~" > .gitignore
	echo -e "vgcore*\n*.log\na.out\n.vscode*" >> .gitignore
	echo -e ".bash_history\n.history" >> .gitignore
	echo $(NAME) >> .gitignore

style:
	/home/${USER}/coding-style-checker/coding-style.sh . .
	echo; grep -v MAJOR:C-O1 coding-style-reports.log || true; echo
	rm -f coding-style-reports.log

tests_run:	all
	./tests/tester.sh
