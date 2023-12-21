/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:49:29 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/20 17:36:02 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(t_vars *vars)
{
	t_kv	*tmp;

	if (!vars->envv)
		ft_printf("\n");
	tmp = vars->envv;
	while (tmp)
	{
		if (tmp->id == 'x')
		{
			if (tmp->val)
				printf("%s=%s\n", tmp->key, tmp->val);
			else
				printf("%s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

void	ft_export(t_vars *vars)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (vars->p_start->prog[i])
	{
		while (vars->p_start->prog[i])
		{
			key = ft_exp_key(vars, vars->p_start->prog[i]);
			if (!key)
				return ;
			value = ft_exp_value(vars, vars->p_start->prog[i]);
			ft_add_envv(vars, key, value, 0);
			ft_new_envp(vars);
			i++;
		}
	}
	else
		ft_export_print(vars);
}

void	ft_unset(t_vars *vars)
{
	char	*key;
	int		i;

	i = 1;
	key = vars->p_start->prog[i];
	while (key)
	{
		ft_remove_envv(vars, key);
		ft_new_envp(vars);
		key = vars->p_start->prog[++i];
	}
}

int	ft_cd(t_vars *vars)
{
	char	*cp;

	if (vars->p_start->prog[1] && vars->p_start->prog[2])
		return (ft_printf_fd(2, "cd: too many arguments\n"));
	if (vars->p_start->prog[1])
	{
		cp = (char *)calloc(ft_strlen(vars->p_start->prog[1]) + 1, \
				sizeof(char));
		if (!cp)
			ft_exit(vars, MALLOC_ERROR);
		ft_strlcpy(cp, vars->p_start->prog[1], \
					ft_strlen(vars->p_start->prog[1]) + 1);
	}
	else
		cp = NULL;
	if (!cp)
	{
		if (!ft_return_val(vars, "HOME"))
			return (ft_printf_fd(2, "cd: HOME not set\n"));
		else
		{
			cp = (char *)calloc(ft_strlen(ft_return_val(vars, "HOME")) \
			+ 1, sizeof(char));
			if (!cp)
				ft_exit(vars, MALLOC_ERROR);
			ft_strlcpy(cp, ft_return_val(vars, "HOME"), ft_strlen(ft_return_val(vars, "HOME")) + 1);
		}
	}
	else if (cp[0] != '/')
		ft_check_pot_path(vars, &cp);
	ft_pwd_conc(vars, &cp);
	if (ft_can_form(vars, &cp))
	{
		ft_printf_fd(2, "cd: No such file or directory: %s", \
		vars->p_start->prog[2]);
		return (1);
	}
	return (ft_chdir(vars, &cp));
}
