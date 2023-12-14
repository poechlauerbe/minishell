/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:49 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 18:54:20 by tbenz            ###   ########.fr       */
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

	if (*curpath && *curpath[0] != '/')
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

void	ft_can_form(t_vars *vars, char **curpath)
{
	while (ft_strcmp(*curpath, "./"))
		ft_remove_dot(vars, curpath);
	ft_remove_dot_dot(vars, curpath);
}

int	ft_dot_dot_len(char *cp, int i)
{
/* 	int	len;

	len = 0;
	while (cp[i] == '.' || cp[i] == '/')
	{
		i++;
		len++;
	}
	return (len);
} */

	int	len;

	len = 0;

	if (!ft_strncmp(&cp[i], "/../", 4))
	{
		len += 4;
		i += 4;
	}
	else if (!ft_strncmp(&cp[i], "/..\0", 4))
	{
		len += 3;
		i += 3;
	}
	while (cp[i++] == '/')
		len++;
	return (len);
}
