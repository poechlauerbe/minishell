/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:14:25 by bpochlau          #+#    #+#             */
/*   Updated: 2024/02/26 14:16:40 by bpochlau         ###   ########.fr       */
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
				ft_printf("%s=%s\n", tmp->key, tmp->val);
		}
		tmp = tmp->next;
	}
	vars->exit_code = 0;
}

void	ft_option_error(t_vars *vars, char *prog)
{
	ft_putchar_fd(prog[0], 2);
	ft_putchar_fd(prog[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	vars->exit_code = 2;
}

void	ft_unset(t_vars *vars, char **prg)
{
	char	*key;
	int		i;

	i = 1;
	if (prg[i] && prg[i][0] == '-' && prg[i][1] != '\0')
	{
		err_handler();
		ft_putstr_fd("minishell: unset: ", 2);
		ft_option_error(vars, prg[i]);
		err_handle_free();
		return ;
	}
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

int	ft_cd2(t_vars *vars, char **cp)
{
	if (!ft_return_val(vars, "HOME"))
	{
		ft_print_err_cd(vars, 2);
		return (1);
	}
	else
	{
		if (*cp)
			free (*cp);
		ft_malloc_cp(vars, cp, ft_return_val(vars, "HOME"));
		return (0);
	}
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
	if (!cp || !ft_strcmp(cp, "--"))
	{
		if (ft_cd2(vars, &cp))
			return ;
	}
	else if (cp[0] != '/')
		ft_check_pot_path(vars, &cp);
	ft_pwd_conc(vars, &cp);
	if (ft_can_form(vars, &cp))
		return ;
	ft_chdir(vars, &cp);
}
