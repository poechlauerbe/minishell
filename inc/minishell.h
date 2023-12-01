/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:52:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/01 11:06:28 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define OK 0
# define MALLOC_ERROR 1000

typedef struct s_prg
{
	int				str_c;
	char			oper;
	char			**prog;
	struct s_prg	*next;
}		t_prg;

typedef struct s_vars
{
	char	*inp;
	t_prg	*p_start;
}		t_vars;

/* functions */

/* ft_handle_signals */
// ignores SIGQUIT and handles SIGINT
void	ft_handle_singals(void);
// handles SIGINT
void	ft_handler_s(int signum, siginfo_t *info, void *no);
// checks for input and stores each input in a 2d array
void	ft_check_input(t_vars *vars);

// frees the linked list where the input is stored
void	ft_free_input(t_vars *vars);
// exits and frees all open mallocs
void	ft_exit(t_vars *vars, int errcd);

void	ft_echo(char **str);

// handles the input given to readline
void	ft_input(t_vars *vars);
// prints the current working directory or an error if this is not possible
void	ft_pwd(void);

#endif
