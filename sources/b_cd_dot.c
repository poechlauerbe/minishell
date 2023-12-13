/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:10:13 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/13 18:06:43 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd_conc(t_vars *vars, char **curpath)
{
	char	*fpath;
	char	*pwd;
	int		plen;
	int		pwdlen;
	int		slash;

	if (*curpath[0] != '/')
	{
		plen = ft_strlen(*curpath);
		pwd = ft_return_val(vars, "PWD");
		pwdlen = ft_strlen(ft_return_val(vars, "PWD"));
		slash = 0;
		if (pwd[pwdlen - 1] != '/')
			slash = 1;
		fpath = (char *)malloc(sizeof(char) * (plen + pwdlen + slash + 1));
		ft_strlcpy(fpath, pwd, (pwdlen + 1));
		if (slash)
			ft_strlcat(fpath, "/", pwdlen + 2);
		ft_strlcat(fpath, *curpath, (plen + pwdlen + slash + 1));
	}
	*curpath = fpath;
}

int	ft_remove_dot_counter(char *curpath)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (curpath[++i])
	{
		if (curpath[i] == '.' && curpath[i + 1] == '/')
			i++;
		else
			len++;
	}
	return (len);
}

void	ft_remove_dot(t_vars *vars, char **curpath)
{
	int		len;
	int		i;
	char	*temp;

	len = (ft_remove_dot_counter(*curpath) + 1);
	temp = (char *)ft_calloc(len, sizeof(char));
	if (!temp)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	len = 0;
	while ((*curpath)[++i])
	{
		if ((*curpath)[i] == '.' && (*curpath)[i + 1] == '/')
			i++;
		else
			temp[len++] = (*curpath)[i];
	}
	free (*curpath);
	*curpath = temp;
}

void	ft_can_form(t_vars *vars, char **curpath)
{
	char	**arr;

	while (ft_strcmp(curpath, "./"))
		ft_remove_dot(vars, curpath);
	ft_remove_dot_dot(vars, curpath);
}
