/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:42:38 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/09 17:33:04 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd_error(t_vars *vars)
{
	err_handler();
	perror("getcwd() error");
	err_handle_free();
	vars->exit_code = 1;
}

void	ft_add_pwd(t_vars *vars)
{
	char	*cpwd;
	char	*pwd;
	char	cwd[1024];

	cpwd = ft_strdup("PWD");
	if (!cpwd)
		ft_exit(vars, MALLOC_ERROR, 0);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		pwd = ft_strdup(cwd);
		if (pwd)
			ft_add_envv(vars, cpwd, pwd, 0);
		else
		{
			free(cpwd);
			ft_exit(vars, MALLOC_ERROR, 0);
		}
		vars->exit_code = 0;
	}
	else
	{
		free(cpwd);
		ft_pwd_error(vars);
	}
}
