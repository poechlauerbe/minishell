/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:01 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/17 16:41:50 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_flag = signum + 128;
	}
}

void	ft_handler_remove(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_flag = signum + 128;
	}
}

void	ft_handler_s(int signum)
{
	g_flag = signum + 128;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	ft_handle_signals(void)
{
	signal(SIGINT, ft_handler_s);
	signal(SIGQUIT, (void *)SIG_IGN);
}


// void	ft_handler_s(int signum, siginfo_t *info, void *no)
// {
// 	no = NULL;
// 	g_flag = signum + 128;
// 	if (signum == SIGINT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		write(1, "\n", 1);
// 		rl_redisplay();
// 	}
// 	if (info)
// 		return ;
// 	if (no)
// 		return ;
// }

// void	ft_handle_signals(void)
// {
// 	struct sigaction	act_int;
// 	struct sigaction	act_quit;

// 	act_int.sa_sigaction = ft_handler_s;
// 	sigemptyset(&act_int.sa_mask);
// 	act_int.sa_flags = SA_SIGINFO;
// 	sigaction(SIGINT, &act_int, NULL);
// 	act_quit.sa_sigaction = (void *)SIG_IGN;
// 	sigemptyset(&act_quit.sa_mask);
// 	act_quit.sa_flags = 0;
// 	sigaction(SIGQUIT, &act_quit, NULL);
// }
