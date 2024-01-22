/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:01 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/22 14:42:47 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include <sys/ioctl.h>

void	ft_handler_child(int signum)
{
	(void) signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	// rl_redisplay();
	g_flag = signum + 128;
}

void	ft_handler_remove(int signum)
{
	g_flag = signum + 128;
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();
}

void	ft_handler_s(int signum)
{
	g_flag = signum + 128;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_handle_signals(void)
{
	signal(SIGINT, ft_handler_s);
	signal(SIGQUIT, SIG_IGN);
}
