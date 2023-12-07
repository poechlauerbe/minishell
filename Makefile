# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 15:17:18 by tbenz             #+#    #+#              #
#    Updated: 2023/12/07 11:16:51 by bpochlau         ###   ########.fr        #
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
				exit.c \
				export.c \
				fun_echo.c \
				input.c \
				input_utils.c \
				minishell.c \
				pipe.c \
				signal_handling.c \
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
				${CC} $(SRCS) ${LIBFT} ${LRL} -o ${NAME}

TESTSRC 		= $(addprefix $(SRCS_DIR),\
				exit.c \
				input.c \
				input_utils.c \
				pipe.c \
				testbenny.c)

benny:			$(LIBFT) $(HEADER)
				$(CC) $(TESTSRC) $(LIBFT)

.PHONY:			all clean fclean re rebonus
