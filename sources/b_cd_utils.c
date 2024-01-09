/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:49 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/09 09:50:29 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_malloc_cp(t_vars *vars, char **cp, char *str)
{
	int	len;
	int	i;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			len++;
	}
	*cp = (char *)calloc(len + 1, sizeof(char));
	if (!*cp)
		ft_exit(vars, MALLOC_ERROR);
	len = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'')
			(*cp)[len++] = str[i];
	}
	(*cp)[i] = '\0';
}

void	ft_pwd_conc(t_vars *vars, char **curpath)
{
	char	*fpath;
	char	*pwd;
	int		plen;
	int		pwdlen;
	int		slash;

	if (*curpath && (*curpath)[0] != '/')
	{
		plen = ft_strlen(*curpath);
		pwd = ft_return_val(vars, "PWD");
		pwdlen = ft_strlen(pwd);
		slash = 0;
		if (pwd && pwd[pwdlen - 1] != '/')
			slash = 1;
		fpath = (char *)malloc(sizeof(char) * (plen + pwdlen + slash + 1));
		if (!fpath)
			ft_exit(vars, MALLOC_ERROR);
		ft_strlcpy(fpath, pwd, (pwdlen + 1));
		if (slash)
			ft_strlcat(fpath, "/", pwdlen + 2);
		ft_strlcat(fpath, *curpath, (plen + pwdlen + slash + 1));
		free (*curpath);
		*curpath = fpath;
	}
}

int	ft_can_form(t_vars *vars, char **curpath)
{
	ft_remove_dot(vars, curpath);
	if (ft_remove_dot_dot(vars, curpath))
	{
		vars->exit_code = 1;
		free (*curpath);
		return (1);
	}
	return (0);
}

void	ft_chdir(t_vars *vars, char **curpath)
{
	char	*tmp;
	t_kv	*elem;
	char	*key;

	if (!access(*curpath, F_OK | X_OK))
	{
		if (!chdir(*curpath))
		{
			if (!ft_val_retrieval(vars, "OLDPWD"))
			{
				key = ft_exp_key(vars, "OLDPWD", 0);
            	ft_add_envv(vars, key, ft_return_val(vars, "PWD"), 0);
			}
            else
            	ft_new_value(vars, "OLDPWD", ft_return_val(vars, "PWD"));
			elem = ft_val_retrieval(vars, "PWD");
			elem->val = ft_strdup(*curpath);
			free (*curpath);
			vars->exit_code = 0;
			return ;
		}
		else
			perror("minishell: cd: ");
	}
	tmp = ft_strjoin("minishell: cd: ", vars->p_start->prog[1]);
	if (!tmp)
		ft_exit(vars, MALLOC_ERROR);
	perror(tmp);
	free (*curpath);
	free (tmp);
	vars->exit_code = 1;
}

void	ft_print_err_cd(t_vars *vars, int error)
{
	if (error == 1)
		ft_printf_fd(2, "minishell: cd: too many arguments\n");
	else if (error == 2)
		ft_printf_fd(2, "cd: HOME not set\n");
	vars->exit_code = 1;
}
