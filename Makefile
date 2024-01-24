# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/01/24 14:19:20 by bpochlau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME			= minishell

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

LIBFT 			= ./libraries/libft/libft.a

CC 				= cc

CFLAGS 			= -Wall -Werror -Wextra -g

LRL				= -lreadline

REMOVE 			= rm -f
REMOVE_DIR		= rm -rf

INC_DIR			= ./inc
SRCS_DIR		= ./sources
OBJDIR			= ./objs

HEADER			= $(addprefix $(INC_DIR)/,\
				macros_minishell.h \
				minishell.h)

SRCS 			= $(addprefix $(SRCS_DIR)/,\
				builtins.c \
				builtins2.c \
				b_cd_dot.c \
				b_cd_dotdot.c \
				b_cd_dotdot2.c \
				b_cd_path.c \
				b_cd_slashes.c \
				b_cd_utils.c \
				b_cd_utils2.c \
				b_echo.c \
				b_exit.c \
				b_export_key_utils.c \
				b_export_new_envp.c \
				b_export_value_utils.c \
				b_export_print.c \
				b_export_print_utils.c \
				environment_var.c \
				err_mes_handler.c \
				exit.c \
				expand_home.c \
				expand_home2.c \
				expand_utils.c \
				expand.c \
				free.c \
				input.c \
				input_check_s_count.c \
				input_comb_progs.c \
				input_heredoc.c \
				input_heredoc_utils.c \
				input_new_node.c \
				input_malloc.c \
				input_red_files.c \
				input_resplit.c \
				input_resplit_addon.c \
				input_utils.c \
				key_value.c \
				key_value_remove.c \
				minishell.c \
				pipe.c \
				pipe_utils.c \
				pipe_dir.c \
				prog.c \
				prog_err.c \
				prog_path.c \
				prog_single.c \
				prog_single_files.c \
				input_redirecting.c \
				signal_handling.c \
				shell_variables.c \
				utils.c)

OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJDIR)/%.o)

all:			${LIBFT} ${NAME}

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

${NAME}:		${LIBFT} $(HEADER) $(OBJS)
				${CC} ${OBJS} ${LIBFT} ${CFLAGS} ${LRL} -o ${NAME}
				@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"
				@echo

${LIBFT}:
				@echo
				make all -C libraries/libft

clean:
				make clean -C libraries/libft
				${REMOVE_DIR} ${OBJDIR}
				@echo

fclean:
				${REMOVE} ${NAME}
				make fclean -C libraries/libft
				${REMOVE_DIR} ${OBJDIR}
				@echo "${NAME}: ${RED}${NAME} and libft.a were deleted${RESET}"
				@echo

re:				fclean all

test:			${LIBFT} $(HEADER)
				${CC} -g $(SRCS) ${LIBFT} ${LRL} -o ${NAME}

valgrind:		$(NAME)
				valgrind --suppressions=valgrind_ignore_leaks.txt \
				--leak-check=full --show-leak-kinds=all --track-origins=yes \
				--show-mismatched-frees=yes	--track-fds=yes ./minishell

.PHONY:			all clean fclean re valgrind
