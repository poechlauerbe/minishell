/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:54:41 by thorben           #+#    #+#             */
/*   Updated: 2024/01/09 11:48:59 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    ft_oldpwd(t_vars *vars)
{
    t_kv	*oldpwd;
	t_kv	*pwd;
	char	*tmp;

	oldpwd = ft_val_retrieval(vars, "OLDPWD");
	if (oldpwd && oldpwd->val)
	{
		if (!access(oldpwd->val, F_OK | X_OK))
		{
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
				perror("minishell: cd: ");
		}
		else 
		{
			tmp = ft_strjoin("minishell: cd: ", vars->p_start->prog[1]);
			if (!tmp)
				ft_exit(vars, MALLOC_ERROR);
			perror(tmp);
			free (tmp);
		}
	}
	else
		ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
	vars->exit_code = 1;
}