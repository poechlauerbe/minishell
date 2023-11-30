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

typedef struct s_prg
{
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

#endif
