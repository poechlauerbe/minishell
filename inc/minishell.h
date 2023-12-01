/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:52:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/01 11:19:45 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// included libraries
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

/* key-value list which stores a key and the respective value. Includes pointer
	to the previous and the next element of the list. */
typedef struct s_keyval
{
	char			*key;
	char			*val;
	struct s_keyval	*next;
	struct s_keyval	*prev;
}				t_keyval;

typedef struct s_vars
{
	char		*inp;
	t_prg		*p_start;
	t_keyval	*envv;
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

/* key_value */
/* returns a pointer to the value retrieved with the key or if no matching key
	was found, return NULL */
char	*ft_return_val(t_vars *vars, char *key);
/* removes an environment variable from the key_value list, matching the key.
	Return 0 on success and 1 if a matching key wasn't found. */
int	ft_remove_envv(t_vars *vars, char *key);
/* adds an environment variable to the key_value list or, if the key already
	exists, changes the value of the matching element. */
void	ft_add_envv(t_vars *vars, char *key, char *val);
// retrieves and returns the element with the matching key. Otherwise returns 0.
t_keyval	*ft_val_retrieval(t_vars *vars, char *key);
// compares two strings (here: key-pairs) and returns 0 if they match.
int	ft_strcmp(const char *s1, const char *s2);

/* utils */
// handles the input given to readline
void	ft_input(t_vars *vars);
// prints the current working directory or an error if this is not possible
void	ft_pwd(void);

#endif
