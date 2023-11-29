/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/29 14:07:58 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	ft_handler_s(int signum, siginfo_t *info, void *no)
{
	siginfo_t	*infos;

	infos = info;
	no = NULL;
	if (signum == SIGINT)
		exit(128+ SIGINT);
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
} */

void	ft_init(t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
}

int	main(void)
{
	t_vars	vars;

	ft_init(&vars);
	ft_handle_singals();
	while (1)
	{
		vars.inp = readline("Prompt> $");
		if (!vars.inp)
			(exit(EOF + 128));
		else if(ft_strlen(vars.inp) > 0 && )
			add_history(vars.inp);
		else
		{
			free(vars.inp);
			vars.inp = NULL;
		}
		// if(ft_strcmp(vars.inp, "pwd", 3) == 0)
		// 	printf("%s", getcwd());
		free(vars.inp);
		vars.inp = NULL;
	}
}
