# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/01/03 18:37:56 by tbenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= minishell
NAME_BONUS		= minishell_bonus

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

LIBFT 			= ./libraries/libft/libft.a

CC 				= cc

CFLAGS 		= -Wall -Werror -Wextra -g

LRL				= -lreadline

REMOVE 			= rm -f

INC_DIR			= ./inc
SRCS_DIR		= ./sources/
BONUS_SRCS_DIR	= ./bonus_sources/

HEADER			= $(addprefix $(INC_DIR)/,\
				macros_minishell.h \
				minishell.h)

SRCS 			= $(addprefix $(SRCS_DIR),\
				builtins.c \
				b_cd_dot.c \
				b_cd_dotdot.c \
				b_cd_dotdot2.c \
				b_cd_path.c \
				b_cd_slashes.c \
				b_cd_utils.c \
				b_echo.c \
				b_exit.c \
				b_export_key_utils.c \
				b_export_new_envp.c \
				b_export_value_utils.c \
				b_export_print.c \
				b_export_print_utils.c \
				environment_var.c \
				exit.c \
				expand_home.c \
				expand.c \
				free.c \
				input.c \
				input_comb_progs.c \
				input_heredoc.c \
				input_malloc.c \
				input_resplit.c \
				input_utils.c \
				key_value.c \
				key_value_remove.c \
				minishell.c \
				pipe.c \
				pipe_utils.c \
				prog.c \
				input_redirecting.c \
				signal_handling.c \
				shell_variables.c \
				utils.c)

OBJ				= $(SRCS:.c=.o)
OBJ_BONUS 		= $(SRCS_BONUS:.c=.o)

SRCS_BONUS 		= $(addprefix $(BONUS_SRCS_DIR),\
					)

all:			${LIBFT} ${NAME}

${NAME}:		${LIBFT} $(HEADER) $(OBJ)
				${CC} ${OBJ} ${LIBFT} ${CFLAGS} ${LRL} -o ${NAME}
				@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"
				@echo

bonus:			${LIBFT} ${NAME_BONUS}

${NAME_BONUS}:	${LIBFT} ${OBJ_BONUS}
				${CC} ${OBJ_BONUS} ${LIBFT} ${CFLAGS} -o ${NAME_BONUS}
				@echo "\n$(NAME): $(GREEN)$(NAME) was compiled with Bonus.$(RESET)"
				@echo

${LIBFT}:
				@echo
				make all -C libraries/libft

%.o: %.c
				${CC} ${CFLAGS} -c $< -o $@

clean:
				make clean -C libraries/libft
				${REMOVE} ${OBJ} ${OBJ_BONUS}
				@echo

fclean:
				${REMOVE} ${NAME} ${NAME_BONUS}
				make fclean -C libraries/libft
				${REMOVE} ${OBJ} {OBJ_BONUS}
				@echo "${NAME}: ${RED}${NAME}, ${NAME_BONUS} and libft.a were deleted${RESET}"
				@echo

re:				fclean all

rebonus:		fclean ${NAME_BONUS}

test:			${LIBFT} $(HEADER)
				${CC} -g $(SRCS) ${LIBFT} ${LRL} -o ${NAME}

valgrind:		$(NAME)
				valgrind --suppressions=valgrind_ignore_leaks.txt \
				--leak-check=full --show-leak-kinds=all --track-origins=yes \
				--verbose --show-mismatched-frees=yes --read-var-info=yes \
				--track-fds=yes --trace-children=yes ./minishell

.PHONY:			all clean fclean re rebonus valgrind
