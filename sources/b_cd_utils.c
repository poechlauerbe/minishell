/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:49 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/18 11:36:46 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_home(t_vars *vars, char **curpath)
{
	char	*fpath;
	char	*pwd;
	int		plen;
	int		pwdlen;
	int		slash;

	if (*curpath && (*curpath)[0] == '~')
	{
		plen = ft_strlen(&(*curpath)[1]);
		pwd = ft_return_val(vars, "HOME");
		pwdlen = ft_strlen(ft_return_val(vars, "HOME"));
		slash = 0;
		if (pwd[pwdlen - 1] != '/')
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
		pwdlen = ft_strlen(ft_return_val(vars, "PWD"));
		slash = 0;
		if (pwd[pwdlen - 1] != '/')
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
		return (1);
	return (0);
}

int	ft_chdir(t_vars *vars, char **curpath)
{
	if (!access(*curpath, F_OK | X_OK))
	{
		if (!chdir(*curpath))
		{
			ft_new_value(vars, "OLDPWD", ft_return_val(vars, "PWD"));
			ft_new_value(vars, "PWD", *curpath);
			free (*curpath);
			return (0);
		}
		else
			perror("cd");
	}
	perror("access");
	free (*curpath);
	return (1);
}
