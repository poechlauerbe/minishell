/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:54:41 by thorben           #+#    #+#             */
/*   Updated: 2024/02/09 17:27:45 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_oldpwd_access(t_vars *vars, t_kv *oldpwd)
{
	char	*tmp;
	t_kv	*pwd;

	if (!chdir(oldpwd->val))
	{
		pwd = ft_val_retrieval(vars, "PWD");
		tmp = pwd->val;
		pwd->val = oldpwd->val;
		oldpwd->val = tmp;
		ft_printf("%s\n", pwd->val);
		vars->exit_code = 0;
		return ;
	}
	else
	{
		err_handler();
		perror("minishell: cd: ");
		err_handle_free();
	}
}

void	ft_oldpwd(t_vars *vars)
{
	t_kv	*oldpwd;

	oldpwd = ft_val_retrieval(vars, "OLDPWD");
	if (oldpwd && oldpwd->val)
	{
		if (!access(oldpwd->val, F_OK | X_OK))
			ft_oldpwd_access(vars, oldpwd);
		else
		{
			err_handler();
			ft_putstr_fd("minishell: cd: ", 2);
			perror(vars->p_start->prog[1]);
			err_handle_free();
		}
	}
	else
	{
		err_handler();
		ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
		err_handle_free();
	}
	vars->exit_code = 1;
}

void	ft_new_oldpwd(t_vars *vars, char *key, char *val)
{
	t_kv	*tmp;
	char	*new;

	if (val && val[0])
	{
		new = ft_strdup(val);
		if (!new)
			ft_exit(vars, MALLOC_ERROR, 0);
	}
	else
		new = NULL;
	tmp = ft_val_retrieval(vars, key);
	if (tmp && tmp->val)
	{
		free(tmp->val);
		tmp->val = new;
	}
	else if (tmp)
		tmp->val = new;
}

void	ft_chdir_pwd_envv(t_vars *vars, char **curpath)
{
	char	*key;
	char	*new_oldpwd;

	if (!ft_val_retrieval(vars, "OLDPWD"))
	{
		key = ft_exp_key(vars, "OLDPWD", 0);
		new_oldpwd = ft_strdup(ft_return_val(vars, "PWD"));
		if (!new_oldpwd)
			ft_exit(vars, MALLOC_ERROR, 0);
		ft_add_envv(vars, key, new_oldpwd, 0);
	}
	else
		ft_new_oldpwd(vars, "OLDPWD", ft_return_val(vars, "PWD"));
	ft_add_pwd(vars);
	free (*curpath);
}

void	ft_chdir(t_vars *vars, char **curpath)
{
	if (!access(*curpath, F_OK | X_OK))
	{
		if (!chdir(*curpath))
		{
			ft_chdir_pwd_envv(vars, curpath);
			return ;
		}
	}
	err_handler();
	ft_putstr_fd("minishell: cd: ", 2);
	perror(vars->p_start->prog[1]);
	err_handle_free();
	free (*curpath);
	vars->exit_code = 1;
}
