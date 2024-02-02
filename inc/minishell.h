/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:50:22 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/02 13:53:59 by bpochlau         ###   ########.fr       */
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
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>

// global variable
extern int	g_flag;

// for the redirect sign - to handle multiple in- and out-files
typedef struct s_red
{
	char			oper;
	char			*file;
	char			*heredoc;
	int				hdoc_flag;
	struct s_red	*next;
}		t_red;

typedef struct s_prg
{
	int				str_c;
	char			oper;
	t_red			*in_file;
	t_red			*out_file;
	char			*heredoc;
	int				hdoc_flag;
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
	char			*inp;
	t_prg			*p_start;
	int				pipe_count;
	t_kv			*envv;
	unsigned char	exit_code;
	char			**envp;
	int				alloc;
	int				no_exec;
	int				*pid;
	int				*fd;
	int				tmp_count;
	int				fd_open_in;
	int				fd_open_out;
	int				std_in;
	int				std_out;
	char			*path;
}		t_vars;

typedef struct s_quote
{
	int		sq;
	int		dq;
	int		i;
	int		len;
	char	*value;
}				t_quote;

typedef struct s_count
{
	int	i;
	int	j;
}		t_count;

/* functions */

/* b_cd_dot */
/* dot components and any slash characters that separate them from the next
	component are deleted*/
void		ft_remove_dot(t_vars *vars, char **curpath);
// createst new curpath removing single dots
void		ft_cur_wo_dot(t_vars *vars, char **curpath, int len);
// counts the length of the string that shall be created
int			ft_remove_dot_counter(char *curpath);

/* b_cd_dotdot */
// removes dotdot and preceding element
int			ft_remove_dot_dot(t_vars *vars, char **cp);
/* handles the loop to create temp. new string which can then be passed to
	curpath */
int			ft_remove_dd2(t_vars *vars, char **temp, int i);
// creates the new current path variable
void		ft_create_cp(t_vars *vars, char **cp, int i, int cl);
/* if the dotdot has preceding elements, this function creates a new curpath
	where the dotdot and the preceding element are omitted */
void		ft_create_cp2(char **cp, int cl, int i, char **tmp);
// tests whether the path indicated before i is a valid address
int			ft_test_dir(t_vars *vars, char **cp, int i);

/* b_cd_dotdot2 */
// returns the length of the preceding element
int			ft_remove_dd_currlen(char *cp, int i);
// returns the length of the dotdot element to be removed including brackets
int			ft_dot_dot_len(char *cp, int i);

/* b_cd_path */
/* tests the combinations of the path entered and those stored in CDPATH; if a
	valid path is encounterd, it is returned */
void		ft_check_pot_path(t_vars *vars, char **curpath);
/* if no valid path is found with the combinations stored in CDPATH, curpath is
	set to ./curpath which consecutively will be replaced with the current
	directory */
void		ft_check_path_null(t_vars *vars, char **curpath);
// tests if one of the different paths in CDPATH exists
char		*ft_diff_paths(t_vars *vars, char *path, char **curpath);
// joins the current path in CDPATH with the curpath and returns the string
char		*ft_create_full_path(t_vars *vars, char *path, char **cpath);

/* b_cd_slashes */
// calls the different functions to remove slashes
void		ft_remove_slashes(t_vars *vars, char **cp);
// removes any trailing slashes from curpath
void		ft_remove_trails(t_vars *vars, char **cp);
// removes non-leading slashes (and non-trailing) slashes from curpath
void		ft_remove_nls(t_vars *vars, char **cp);
/* returns the length of curpath after removing all the non-leading and
	non-trailing slashes from curpath */
int			ft__remove_nl_len(char *cp);
/* removes leading slashes if there are three or more from curpath and leaves
	only one */
void		ft_remove_ls(t_vars *vars, char **cp);

/* b_cd_utils */
// callocs a new current path
void		ft_malloc_cp(t_vars *vars, char **cp, char *str);
// if curpath doesn't start with a dot, joins the PWD with curpath
void		ft_pwd_conc(t_vars *vars, char **curpath);
// converts curpath according to the canonical form
int			ft_can_form(t_vars *vars, char **curpath);
// prints an error message an sets the error code
void		ft_print_err_cd(t_vars *vars, int error);

/* b_cd_utils2 */
/* if OLDPWD is set, and cd - is received as input, changes
	PWD to OLDPWD and OLDPWD to PWD */
void		ft_oldpwd(t_vars *vars);
// if possible, changes the current directory to curpath
void		ft_chdir(t_vars *vars, char **curpath);
// changes the OLDPWD and PWD envv if they exist
void		ft_chdir_pwd_envv(t_vars *vars, char **curpath);

/* b_exit */
void		ft_exit_prog(t_vars *vars, char **prog);

/* b_export_key_utils */
// checks if quotes are properly closed
int			ft_check_enclosing(char **arg, t_vars *vars);
// extracts the key of argument
char		*ft_copy_key(t_vars *vars, char *arg);
/* returns a copy of the key if it is valid or NULL if it is not valid
	func is set to 0 if export calls, and to 1 if shvar calls */
char		*ft_exp_key(t_vars *vars, char *arg, int func);
/* checks the key for valid input; if func is 0 (keychecker called by export)
	prints error messages; if func is set to 1 (called by shvar) doesn't print
	error messages */
int			ft_exp_keychecker(t_vars *vars, char *arg, char *comp, int func);
// gets the length
int			ft_key_len(char *arg);

/* b_export_new_envp */
/* creates a new array of envp variables which can be passed to child processses
	if there is an existing allocation already, it frees these variables first
*/
void		ft_new_envp(t_vars *vars);
// frees the existing envp variables
void		ft_free_envp(char **envp);
// mallocs the new envp
void		ft_malloc_envp(t_vars *vars, char ***arr);
// allocates a new envp from the envv variables
void		ft_create_envp(t_vars *vars, int i, t_kv *tmp2, char ***arr);
// counts the number of envv variables, for which memory has to be allocated
int			ft_envp_len(t_vars *vars);

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
// prints an error message an sets the exit code for an invalid key
void		ft_key_err_print(t_vars *vars, char *key, char *val);

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
/* erases a key-value combination from the saved variables and adjusts the
	respective pointers */
void		ft_unset(t_vars *vars, char **prg);
/* if directory exists and one has the necessary rights, moves one to the dir
	entered*/
void		ft_cd(t_vars *vars);
/* handles cd and cd -- which should resolve to the home directory or returns an
	error if HOME is not set */
int			ft_cd2(t_vars *vars, char **cp);
// description
void		ft_option_error(t_vars *vars, char *prog);

/* builtins2 */
/* prints the env variables when it does not have arguments, otherwise tries to
	add a key value pair */
void		ft_export(t_vars *vars);
// creates an environment variable
void		ft_export_prog(t_vars *vars, char **prog, int i);

/* signal_handling */
// ignores SIGQUIT and handles SIGINT
void		ft_handle_signals(void);
// handles SIGINT
void		ft_handler_s(int signum);
void		ft_handler_remove(int signum);
void		ft_handler_child(int signum);

/* environment_var */
// creates a struct that stores all the environment values in order
void		ft_create_env(t_vars *vars, char **envp);
// returns the last kvue entry
t_kv		*ft_last_entry(t_kv *elem);
//  updates the underscore variable
void		ft_add_underscore(t_vars *vars, char **prg);

/* exit */
void		ft_err_too_many_args(t_vars *vars);
// prints an error message
// void		err_mes(void);
// frees the linked list where the input is stored
void		ft_free_input(t_vars *vars);
// exits and frees all open mallocs
void		ft_exit(t_vars *vars, int errcd, int message);
/* resets the input of the shell and returns 1 - might have to add free
	additional functions, depending on other elements that might be added  */
void		ft_reset(t_vars *vars);
// frees the environment variables
void		ft_free_envv(t_vars *vars);

/* expand */
void		ft_expand_all_vars(t_vars *vars);
void		ft_expander(t_vars *vars, char **arg, t_quote *quote);
// function for $?
int			ft_check_exit_code(t_vars *vars);

/* expand_home */
// expands to home with consecutive path
void		ft_home(t_vars *vars, char **curpath);
// opens the /etc/passwd file
void		ft_etc_passwd(t_vars *vars, char **str, char **tmp);
// expands home
void		ft_home_expand(t_vars *vars, char **str);
// expands to user home directory
void		ft_user_home(t_vars *vars, char **str, char **tmp);
// retrieves the home directory of the user
void		ft_home_usr_retrvl(t_vars *vars, char **home, char **usr);

/* expand_home2 */
void		ft_etc_passwd_loop(t_vars *vars, char **str, char **tmp, int fd);
void		ft_etc_arr_free(char ***arr, char **line);

/* expand_utils */
int			ft_varlen(char *arg, t_quote *quote);
int			ft_exp_remove_spaces(char *str, char *arg, int *i, int *j);

/* free */
void		ft_free_pipe_fd_and_pid(t_vars *vars);
void		ft_free_input(t_vars *vars);
void		ft_close_var_open(t_vars *vars);
void		ft_free_reds(t_red **file);
void		ft_free_t_prg(t_prg *temp);

/* fun echo */
// writes to the shell in standard output
void		ft_echo(t_vars *vars, char **str);

/* input utils*/
// check input for quotes
void		ft_check_quotes(char **inp);
void		ft_quote_remover(t_vars *vars);

/* input */
// checks for input and stores each input in a 2d array
void		ft_check_input(t_vars *vars);

/* input_check_s_count */
void		ft_check_string_count(t_vars *vars, char *inp);

/* input_comb_progs */
void		ft_comb_progs(t_vars *vars);

/* input_new_node */
void		ft_new_node(t_vars *vars, t_prg **temp, char **inp);

/* input_malloc */
void		ft_malloc_prog_2d_str(t_vars *vars, char *inp);

/* input_red_files */
void		ft_red_file(t_vars *vars, t_prg *lst);
int			ft_check_redirect_file(t_vars *vars);

/* input_redirecting */
// clean all nodes after storing them in the programs
void		ft_cleanup_reds(t_vars *vars);
// clean list if there is a redirecting sign at the beginning
void		ft_cleanup_lst(t_vars *vars);

/* input_resplit */
int			ft_strlen_resplit(char *str, int *i);
void		ft_check_resplit(t_vars *vars, char *str, t_prg *prg);

/* input_resplit_addon */
void		ft_check_addon_resplit(t_vars *vars, char *str, t_prg *prg);

/* key_value */
// changes the value of a given key value to val
void		ft_new_value(t_vars *vars, char *key, char *val);
/* returns a pointer to the value retrieved with the key or if no matching key
	was found, return NULL */
char		*ft_return_val(t_vars *vars, char *key);
/* adds an environment variable to the key_value list or, if the key already
	exists, changes the value of the matching element. */
void		ft_add_envv(t_vars *vars, char *key, char *val, int id);
// retrieves and returns the element with the matching key. Otherwise returns 0.
t_kv		*ft_val_retrieval(t_vars *vars, char *key);

/* input heredoc */
void		ft_heredoc_exec(t_vars *vars, t_prg *prog);
void		ft_heredoc(t_vars *vars, t_prg *prog);
void		ft_add_on_heredoc_str(t_vars *vars, t_prg *prog, char *str);
void		ft_err_m_hered(t_prg *prog, int line_num);
int			ft_check_enclosing_heredoc(char **arg, t_vars *vars);

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

/* minishell */
// the actual minishell which gets input from readline, executes it and free inp
void		ft_minishell_inner_loop(t_vars *vars);
// handles the input to the minishell (if it is not EOF)
void		ft_minishell_input_handling(t_vars *vars);

/* pipe */
// pipe function
void		ft_check_input_file(t_vars *vars, t_prg *temp, t_red *reds);
void		ft_check_output_file(t_vars *vars, t_prg *temp, t_red *reds);
void		ft_pipecount(t_vars *vars);
void		ft_pipe(t_vars *vars);

/* pipe_utils */
// counts how many pipes are in the input
void		ft_pipecount(t_vars *vars);
// closes all the open pipes of the pipeloop
void		ft_close_pipes(int pipe_nr, int *fd);
int			ft_check_command_path(char *file, t_vars *vars);
void		ft_wait_childs(t_vars *vars, int commands);

// checks if the input file is accesable
int			ft_check_in_access(char *file, t_vars *vars);
// checks if the output file is accesable
int			ft_check_out_access(char *file, t_vars *vars);

/* prog */
int			ft_check_dir(t_vars *vars, char *str);
void		ft_check_prog(t_vars *vars, t_prg *prog);

/* prog_err */
void		ft_no_rights(t_vars *vars, char *prog, char **to_free);
void		ft_is_dir(t_vars *vars, t_prg *prog);
void		ft_prog_not_found(t_vars *vars, t_prg *prog);

/* prog_path */
void		ft_check_path(t_vars *vars, t_prg *prog);

/* redirect_utils */
void		ft_red_new_node(t_vars *vars, t_red **lst, char *file, char oper);

int			ft_builtin_single_prog(t_vars *vars, t_prg *prog);
int			ft_builtin(t_vars *vars, t_prg *prog);

void		ft_prog_not_found(t_vars *vars, t_prg *prog);

/* shell variables */
// checks whether a shell variable has to be created
int			ft_check_shvar(t_vars *vars, t_prg *prog);
/* checks whether the instructions are valid and all the shell variables can be
	created */
int			ft_check_validity(t_vars *vars, t_prg *prog);
/* creates the validity of the key and value of a possible shell variable
 	returns 0 if the key and value are valid
	returns 1 if the key and value entered are invalid */
int			ft_check_key_val(t_vars *vars, char *prg);
// creates the new shell variables
void		ft_create_shvar(t_vars *vars, t_prg *prog, int i);
// returns an error message for directories entered into bash
void		ft_is_dir(t_vars *vars, t_prg *prog);

/* utils */
// sets all variables to zero and initiates envp variables
void		ft_init(t_vars *vars, int argc, char **argv, char **envp);
// prints the current working directory or an error if this is not possible
void		ft_pwd(t_vars *vars);
// sets the values for the tmp variable (except for key and value)
void		ft_set_val(t_vars *vars, t_kv **var, t_kv **tmp);
// compares two strings (here: key-pairs) and returns 0 if they match.
int			ft_strcmp(const char *s1, const char *s2);
// checks it there are any open quotes in the command
int			ft_enclosing_open_quotes(t_vars *vars, t_quote quote);

// void		ft_remove_envp(t_vars *vars, char *key);
// void		ft_malloc_envpr(t_vars *vars, char ***arr, char *key);

/* prog_single_files */
int			ft_c_infile_sp(t_vars *vars, t_prg *temp, t_red *reds);
int			ft_c_outfile_sp(t_vars *vars, t_prg *temp, t_red *reds);
int			ft_check_files_sp(t_vars *vars, t_prg *prog);

void		err_handler(void);
void		err_handle_free(void);
void		ft_start_err(t_vars *vars, char *temp, int i, int j);

#endif
