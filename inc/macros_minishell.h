/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:29 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/07 12:06:24 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_MINISHELL_H
# define MACROS_MINISHELL_H

# define OK 0
# define MALLOC_ERROR 1000
# define PIPE_ERROR 1100
# define FORK_ERROR 1200
# define WAITPID_ERROR 1300
# define DUP_ERROR 1400

# define O_PIPE 124
//  >
# define O_RED_OUTPUT 62
//  <
# define O_RED_INPUT 60

#endif
