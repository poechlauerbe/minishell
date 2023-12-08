/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_minishell.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:29 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/08 15:30:16 by bpochlau         ###   ########.fr       */
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
# define OPEN_FILE_ERROR 1500

# define O_PIPE 124
//  >
# define O_RED_OUTPUT 62
//  >>
# define O_APP_OUT 63
//  <
# define O_RED_INPUT 60


#endif
