/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:49:29 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 12:29:44 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// something is not working well here
void	ft_env(t_vars *vars)
{
	t_kv	*tmp;

	if (!vars->envv)
		ft_printf("\n");
	tmp = vars->envv;
	while (tmp)
	{
		if (tmp->id == 'x')
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
}

void	ft_export(t_vars *vars)
{
	int		i;
	char	*id;
	char	*value;

	i = 1;
	if (vars->p_start->prog[i])
	{
		while (vars->p_start->prog[i])
		{
			id = ft_exp_key(vars, vars->p_start->prog[i]);
			if (!id)
				return ;
			value = ft_exp_value(vars, vars->p_start->prog[i]);
			if (!value)
				return ;
			ft_add_envv(vars, id, value, 0);
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
		key = vars->p_start->prog[++i];
	}
}

/* void	ft_cd(t_vars *vars)
{
	int		acc_c;
	char	*curpath;

	if (vars->p_start->prog[2])
		return (ft_printf_fd(2, "cd: too many arguments"));
	curpath = vars->p_start->prog[1];
	if (!curpath && !ft_return_val(vars, "HOME"))
		return (ft_printf_fd(2, "cd: HOME not set"));
	else if (!curpath && !ft_return_val(vars, "HOME"))
		curpath = ft_return_val(vars, "HOME");
	else if (curpath[0] == '/')
		curpath = curpath;
	else
	{
		if (curpath[0] == '.')
		//shouldn't test fpr acces, just if path exists
			ft_access_path(curpath);
		else
			ft_check_pot_path(vars, &curpath);
	}
	ft_pwd_conc(vars, &curpath);
	ft_can_form(vars, curpath);
} */
