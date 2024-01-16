/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:51:31 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/16 13:53:33 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	ft_create_shvar(t_vars *vars, t_prg *prog, int i)
{
	char	*key;
	char	*val;


	key = ft_exp_key(vars, prog->prog[i], 1);
	val = ft_exp_value(vars, prog->prog[i]);
	if (!key || ! val)
	{
		if (key)
			free (key);
		if (val)
			free (val);
		return ;
	}
	ft_add_envv(vars, key, val, 1);
}

void	ft_prog_not_found_shvar(t_vars *vars, char *arg)
{
	char *nfd;

	nfd = ft_strjoin(arg, ": command not found\n");
	if (!nfd)
		ft_exit(vars, MALLOC_ERROR);
	ft_printf_fd(2, nfd);
	free (nfd);
	vars->exit_code = 127;
	exit(127);
}

int	ft_check_validity(t_vars *vars, t_prg *prog)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (prog->prog[i])
	{
		if (!ft_strchr(prog->prog[i], '=') && i == 0)
			return (1);
		if (!ft_strchr(prog->prog[i], '=') && i > 0)
		{
			ft_prog_not_found_shvar(vars, prog->prog[i]);
			return (2);
		}
		key = ft_exp_key(vars, prog->prog[i], 1);
		val = ft_exp_value(vars, prog->prog[i]);
		if (!key || ! val)
		{
			if (key)
				free (key);
			if (val)
				free (val);
			ft_prog_not_found_shvar(vars, prog->prog[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int	ft_check_shvar(t_vars *vars, t_prg *prog)
{
	int	i;
	int	val;

	i = 0;
	val = ft_check_validity(vars, prog);
	if (!val)
	{
		while (prog->prog[i])
		{
			ft_create_shvar(vars, prog, i);
			i++;
		}
		return (0);
	}
	else if (val == 1)
		return (1);
	else
		return (0);
}
