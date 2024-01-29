/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:01 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/25 17:31:06 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handler_child(int signum)
{
	(void) signum;
	g_flag = signum + 128;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	ft_handler_remove(int signum)
{
	g_flag = signum + 128;
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
