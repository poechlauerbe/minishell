/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:10:13 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/13 17:00:47 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* void	ft_pwd_conc(t_vars *vars, char **curpath)
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
} */

/* int	ft_remove_dot_counter(char *curpath)
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
} */

int	ft_remove_dd_currlen(char *cp, int i)
{
	int	len;

	len = 0;
	while (cp[i] && cp[i++] != '/')
		len++;
	len++;
	return (len);
}

int	ft_test_dir(t_vars *vars, char **cp, int i)
{
	char	*dir;
	int		j;

	if (i == 2|| ( (*cp)[i - 2] == '.' && (*cp)[i - 3] == '.'))
		return (1);
	dir = (char *)calloc(i, sizeof(char));
	if (!dir)
		ft_exit(vars, MALLOC_ERROR);
	j = -1;
	while (++j < (i - 1))
		dir[j] = (*cp)[j];
	dir[j] = '\0';
	if (access(dir, F_OK))
	{
		free(dir);
		free (*cp);
		return (1);
	}
	free (dir);
	return (0);
}

int	ft_dot_dot_len(char *cp, int i)
{
	int	len;

	len = 0;
	while (cp[i] == '.' || cp[i] == '/')
	{
		i++;
		len++;
	}
	return (len);
}

void	ft_create_cp(char **cp, int i, int cl, int len)
{
	int		j;
	int		k;
	char	*temp;

	temp = (char *)ft_calloc((len + 1), sizeof(char));
	k = -1;
	while ((*cp)[++k] && k < (i - cl))
		temp[k] = (*cp)[k];
	j = 3;
	i += j;
	while ((*cp)[i])
	{
		temp[k++] = (*cp)[i];
		i++;
	}
	temp[k] = '\0';
	free (*cp);
	*cp = temp;
}

int	ft_remove_dot_dot(t_vars *vars, char **cp)
{
	int	tlen;
	int	len;
	int	curr_len;
	int	i;

	len = 0;
	i = -1;
	while ((*cp)[++i])
	{
		tlen = ft_strlen(*cp);
		len = tlen;
		if ((*cp)[i] == '.' && (*cp)[i + 1] == '.' &&
			((*cp)[i + 2] == '/' || (*cp)[i + 2] == '\0'))
		{
			if (ft_test_dir(vars, cp, i))
				return (1);
			len -= (curr_len + ft_dot_dot_len(*cp, i));
			ft_create_cp(cp, i, curr_len, len);
			i = 0;
		}
		if (i == 0 || (*cp)[i - 1] == '/')
			curr_len = ft_remove_dd_currlen(*cp, i);
	}
	return (0);
}

/* void	ft_can_form(t_vars *vars, char **curpath)
{
	char	**arr;

	while (ft_strcmp(curpath, "./"))
		curpath = ft_quit_dot(vars, curpath, len);

	if (ft_strcmp(curpath, "./"))
} */
