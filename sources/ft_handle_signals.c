/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:56:01 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/29 14:03:59 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_handler_s(int signum, siginfo_t *info, void *no)
{
	siginfo_t	*infos;

	infos = info;
	no = NULL;
	if (signum == SIGINT)
	/* if there is a foreground process running, the process will send the
	process a SIGINT, otherwise a new prompt will be issued */
		exit(128 + SIGINT);
}

void	ft_handle_singals(void)
{
	struct sigaction	act_int;
	struct sigaction	act_quit;

	act_int.sa_sigaction = ft_handler_s;
	sigemptyset(&act_int.sa_mask);
	act_int.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act_int, NULL);

	act_quit.sa_sigaction = (void *)SIG_IGN;
	sigemptyset(&act_quit.sa_mask);
	act_quit.sa_flags = 0;
	sigaction(SIGQUIT, &act_quit, NULL);
}
