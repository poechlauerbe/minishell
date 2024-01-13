/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:29 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/12 08:43:22 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_MINISHELL_H
# define MACROS_MINISHELL_H

# define NOT_DEFINED 999

# define NOT_OK -1
# define OK 0
# define MALLOC_ERROR 1000
# define PIPE_ERROR 1100
# define FORK_ERROR 1200
# define WAITPID_ERROR 1300
# define DUP_ERROR 1400
# define OPEN_FILE_ERROR 1500

// standard error codes bash:
# define NO_SUCH_FILE_OR_DIRECTORY 1
# define NUMERIC_ARGUMENTS_REQUIRED 2
# define SYNTAX_ERROR 2
# define PERMISSION_DENIED 126
# define IS_A_DIRECTORY 126
# define COMMAND_NOT_FOUND 127

// for ft_builtin_check:
# define USED 100
# define NOT_USED 200

// codes for pipe and input redirections
# define O_PIPE 124
//  >
# define O_RED_OUTPUT 62
//  >>
# define O_APP_OUT 63
//  <
# define O_RED_INPUT 60
//  <<
# define O_HEREDOC 61

// Text macros:
# define M_SYN "bash: syntax error near unexpected token `"

#endif
