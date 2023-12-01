/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:21:46 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/01 11:07:58 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void	ft_input(t_vars *vars)
{
	if (!vars->inp)
		exit(EOF + 128);
	else if (ft_strlen(vars->inp) > 0)
		add_history(vars->inp);
	if (ft_strncmp(vars->inp, "exit", 4) == 0)
		exit(0);
	if(ft_strncmp(vars->inp, "pwd", 3) == 0)
		ft_pwd();
	if(ft_strncmp(vars->p_start->prog[0], "echo", 4) == 0)
		ft_echo(vars->p_start->prog);
}
