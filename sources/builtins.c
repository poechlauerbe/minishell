/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:14:25 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/13 12:05:19 by bpochlau         ###   ########.fr       */
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
		}
		tmp = tmp->next;
	}
	vars->exit_code = 0;
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
			key = ft_exp_key(vars, vars->p_start->prog[i], 0);
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

void	ft_unset(t_vars *vars, char **prg)
{
	char	*key;
	int		i;

	i = 1;
	key = prg[i];
	while (key)
	{
		ft_remove_envv(vars, key);
		vars->exit_code = 0;
		ft_new_envp(vars);
		key = prg[++i];
	}
	ft_add_underscore(vars, prg);
}

void	ft_cd(t_vars *vars)
{
	char	*cp;

	if (vars->p_start->prog[1] && vars->p_start->prog[2])
		return (ft_print_err_cd(vars, 1));
	else if (!ft_strcmp(vars->p_start->prog[1], "-"))
	{
		ft_oldpwd(vars);
		return ;
	}
	else if (vars->p_start->prog[1])
		ft_malloc_cp(vars, &cp, vars->p_start->prog[1]);
	else
		cp = NULL;
	if (!cp || !strcmp(cp, "--"))
	{
		if (!ft_return_val(vars, "HOME"))
			return (ft_print_err_cd(vars, 2));
		else
		{
			if (cp)
				free (cp);
			ft_malloc_cp(vars, &cp, ft_return_val(vars, "HOME"));
		}
	}
	else if (cp[0] != '/')
		ft_check_pot_path(vars, &cp);
	ft_pwd_conc(vars, &cp);
	if (ft_can_form(vars, &cp))
		return ;
	ft_chdir(vars, &cp);
}
