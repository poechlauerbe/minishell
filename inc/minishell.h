/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:52:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 16:49:28 by tbenz            ###   ########.fr       */
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
	char		**envp;
	t_keyval	*envv;
}		t_vars;

typedef struct s_quote
{
	int		sq;
	int		dq;
	int		i;
	int		len;
	char	*value;
}				t_quote;

/* functions */

/* b_export_key_utils */
// checks if parenthesis are properly closed
int			ft_check_enclosing(char *arg);
// extracts the key of argument
char		*ft_copy_key(char *arg);
// returns a copy of the key if it is valid or NULL if it is not valid
char		*ft_exp_key(char *arg);
// checks the key for valid input
int			ft_exp_keychecker(char *arg, char *comp);
// gets the length
int			ft_key_len(char *arg);

/* b_export_value_utils */
// creates a string with the value that is then being returned
char		*ft_create_value(char *arg);
// copies the value from the argument to a malloc'd string
void		ft_copy_value(t_quote *quote, char *arg);
/* extracts the value of a key value pair; if only the key is put, it returns a
	str that contains only a null terminator; if parenthesis are not properly
	closed it returns NULL */
char		*ft_exp_value(char *arg);
// sets the ints of the struct to 0 and the char to NULL
void		ft_init_quote(t_quote *quote);
// gets the length of the string that should be created
void		ft_quote_len(t_quote *quote, char *arg);

/* builtins */
// prints the environment variables present
void		ft_env(t_vars *vars);
/* prints the env variables when it does not have arguments, otherwise tries to
	add a key value pair */
void		ft_export(t_vars *vars);

/* signal_handling */
// ignores SIGQUIT and handles SIGINT
void		ft_handle_singals(void);
// handles SIGINT
void		ft_handler_s(int signum, siginfo_t *info, void *no);

/* exit */
// prints an error message
void		err_mes(void);
// frees the linked list where the input is stored
void		ft_free_input(t_vars *vars);
// exits and frees all open mallocs
void		ft_exit(t_vars *vars, int errcd);
/* resets the input of the shell and returns 1 - might have to add free
	additional functions, depending on other elements that might be added  */
int			ft_reset(t_vars *vars);

/* fun echo */
// writes to the shell in standard output
void		ft_echo(char **str);

/* input utils*/
// create new node in input linked list
void		ft_new_node(t_vars *vars, t_prg **temp, char **inp);
// check input for quotes
void		ft_check_quotes(char **inp);

/* input */
// checks for input and stores each input in a 2d array
void		ft_check_input(t_vars *vars);

/* key_value */
/* returns a pointer to the value retrieved with the key or if no matching key
	was found, return NULL */
char		*ft_return_val(t_vars *vars, char *key);
// handles the else part of the ft_remove_envv function
int			ft_remove_helper(t_vars *vars, t_keyval *tmp);
/* removes an environment variable from the key_value list, matching the key.
	Return 0 on success and 1 if a matching key wasn't found. */
int			ft_remove_envv(t_vars *vars, char *key);
/* adds an environment variable to the key_value list or, if the key already
	exists, changes the value of the matching element. */
void		ft_add_envv(t_vars *vars, char *key, char *val);
// retrieves and returns the element with the matching key. Otherwise returns 0.
t_keyval	*ft_val_retrieval(t_vars *vars, char *key);

/* utils */
// sets all variables to zero and initiates envp variables
void		ft_init(t_vars *vars, int argc, char **argv, char **envp);
// handles the input given to readline
void		ft_input(t_vars *vars);
// prints the current working directory or an error if this is not possible
void		ft_pwd(void);
// compares two strings (here: key-pairs) and returns 0 if they match.
int			ft_strcmp(const char *s1, const char *s2);
#endif
