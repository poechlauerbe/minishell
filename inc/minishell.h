/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:50:22 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 11:22:59 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// included libraries
# include "../libraries/libft/libft.h"
# include "macros_minishell.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

// for the redirect sign - to handle multiple in- and out-files
typedef struct s_red
{
	char			oper;
	char			*file;
	struct s_red	*next;
}		t_red;

typedef struct s_prg
{
	int				str_c;
	char			oper;
	t_red			*in_file;
	t_red			*out_file;
	char			**prog;
	struct s_prg	*next;
}		t_prg;

/* key-value list which stores a key and the respective value. Includes pointer
	to the previous and the next element of the list. */
typedef struct s_kv
{
	char			*key;
	char			*val;
	char			id;
	struct s_kv		*next;
	struct s_kv		*prev;
	struct s_kv		*nxtao;
	struct s_kv		*prvao;
}				t_kv;

typedef struct s_vars
{
	char		*inp;
	t_prg		*p_start;
	int			pipe_count;
	t_kv		*envv;
	char		exit_code;
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

/* b_exit */
void		ft_exit_prog(t_vars *vars,char **prog);

/* b_export_key_utils */
// checks if parenthesis are properly closed
int			ft_check_enclosing(char **arg, t_vars *vars);
// extracts the key of argument
char		*ft_copy_key(t_vars *vars, char *arg);
// returns a copy of the key if it is valid or NULL if it is not valid
char		*ft_exp_key(t_vars *vars, char *arg);
// checks the key for valid input
int			ft_exp_keychecker(char *arg, char *comp);
// gets the length
int			ft_key_len(char *arg);

/* b_export_print */
// orders all the key-value elements alphabetically in a linked list
void		ft_order_envv(t_vars *vars);
// returns the next key-value element
t_kv		*ft_next_kv(t_kv *elem, t_kv *prev, t_kv *last);
// returns the first key-value element
t_kv		*ft_first_kv(t_kv *elem);
// returns the last key-value element
t_kv		*ft_last_kv(t_kv *elem);
/* prints all the environment variables (including the ones that have been
	exported) in alphabetical order */
void		ft_export_print(t_vars *vars);

/* b_export_print_utils */
/* adds an alphabetical ordering for the environment variables and shell
	variables, connecting them via linked list */
void		ft_add_ao(t_vars *vars, t_kv *elem);
/* sets the pointers for the linked list of alphabetically ordered elements */
void		ft_set_ptr(t_vars *vars, t_kv **elem, t_kv *prev);

/* b_export_value_utils */
// creates a string with the value that is then being returned
char		*ft_create_value(t_vars *vars, char *arg);
// copies the value from the argument to a malloc'd string
void		ft_copy_value(t_quote *quote, char *arg);
/* extracts the value of a key value pair; if only the key is put, it returns a
	str that contains only a null terminator; if parenthesis are not properly
	closed it returns NULL */
char		*ft_exp_value(t_vars *vars, char *arg);
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
/* erases a key-value combination from the saved variables and adjusts the
	respective pointers */
void		ft_unset(t_vars *vars);

/* signal_handling */
// ignores SIGQUIT and handles SIGINT
void		ft_handle_signals(void);
// handles SIGINT
void		ft_handler_s(int signum, siginfo_t *info, void *no);

/* environment_var */
// creates a struct that stores all the environment values in order
void		ft_create_env(t_vars *vars, char **envp);
// returns the last kvue entry
t_kv		*ft_last_entry(t_kv *elem);

/* exit */
// prints an error message
// void		err_mes(void);
// frees the linked list where the input is stored
void		ft_free_input(t_vars *vars);
// exits and frees all open mallocs
void		ft_exit(t_vars *vars, int errcd);
/* resets the input of the shell and returns 1 - might have to add free
	additional functions, depending on other elements that might be added  */
int			ft_reset(t_vars *vars);
//
void	ft_free_envv(t_vars *vars);

/* expand */
void		ft_expand_all_vars(t_vars *vars);
void		ft_expander(t_vars *vars, char **arg, t_quote *quote);
// function for $?
int			ft_check_exit_code(t_vars *vars);

/* fun echo */
// writes to the shell in standard output
void		ft_echo(t_vars *vars, char **str);

/* input utils*/
// create new node in input linked list
void		ft_new_node(t_vars *vars, t_prg **temp, char **inp);
// check input for quotes
void		ft_check_quotes(char **inp);
// clean all nodes after storing them in the programs
void		ft_cleanup_reds(t_vars *vars);
// clean list if there is a redirecting sign at the beginning
void		ft_cleanup_lst(t_vars *vars);

/* input */
// checks for input and stores each input in a 2d array
void		ft_check_input(t_vars *vars);

/* key_value */
/* returns a pointer to the value retrieved with the key or if no matching key
	was found, return NULL */
char		*ft_return_val(t_vars *vars, char *key);
/* adds an environment variable to the key_value list or, if the key already
	exists, changes the value of the matching element. */
void		ft_add_envv(t_vars *vars, char *key, char *val, int id);
// retrieves and returns the element with the matching key. Otherwise returns 0.
t_kv		*ft_val_retrieval(t_vars *vars, char *key);

/* key_value_remove */
/* removes an environment variable from the key_value list, matching the key.
	Return 0 on success and 1 if a matching key wasn't found. */
int			ft_remove_envv(t_vars *vars, char *key);
// handles the else part of the ft_remove_envv function
int			ft_remove_helper(t_vars *vars, t_kv *tmp);
// adjusts the links of the linked list
void		ft_remove_links(t_kv **tmp, t_kv **var);
/* adjusts the links of the previous and following element of the one being
	removed for the alphabetical ordering */
void		ft_remove_links_ao(t_kv **tmp);

/* pipe */
// pipe function
void		ft_pipecount(t_vars *vars);
void		ft_pipe_loop(t_vars *vars);

/* prog */
void		ft_check_prog(t_vars *vars, t_prg *prog);

/* redirect_utils */
void		ft_red_new_node(t_vars *vars, t_red **lst, char *file, char oper);

int	ft_builtin_check(t_vars *vars, t_prg *prog);

/* utils */
// sets all variables to zero and initiates envp variables
void		ft_init(t_vars *vars, int argc, char **argv, char **envp);
// prints the current working directory or an error if this is not possible
void		ft_pwd(void);
// sets the values for the tmp variable (except for key and value)
void		ft_set_val(t_vars *vars, t_kv **var, t_kv **tmp);
// compares two strings (here: key-pairs) and returns 0 if they match.
int			ft_strcmp(const char *s1, const char *s2);
#endif
