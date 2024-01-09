/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:39:12 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/08 18:20:57 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_home(t_vars *vars, char **curpath)
{
	char	*fpath;
	char	*pwd;
	int		plen;
	int		pwdlen;

	plen = ft_strlen(&(*curpath)[1]);
	pwd = ft_return_val(vars, "HOME");
	pwdlen = ft_strlen(ft_return_val(vars, "HOME"));
	fpath = (char *)malloc(sizeof(char) * (plen + pwdlen + 1));
	if (!fpath)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcpy(fpath, pwd, (pwdlen + 1));
	ft_strlcat(fpath, &(*curpath)[1], (plen + pwdlen + 1));
	free (*curpath);
	*curpath = fpath;
}

void	ft_etc_passwd_loop(t_vars *vars, char **str, char **tmp, int fd)
{
	char	*line;
	char	**arr;
	int		i;

	line = get_next_line(fd);
	while (line && !*tmp)
	{
		arr = ft_split(line, ':');
		if (!arr)
			ft_exit(vars, MALLOC_ERROR);
		i = 0;
		if (!ft_strcmp(&(*str)[1], arr[0]))
		{
			*tmp = ft_strdup(arr[5]);
			if (!*tmp)
				ft_exit(vars, MALLOC_ERROR);
		}
		free (line);
		line = get_next_line(fd);
		i = 0;
		while (arr[i])
		{
			free (arr[i]);
			i++;
		}
		free (arr);
	}
}

void	ft_etc_passwd(t_vars *vars, char **str, char **tmp)
{
	int		fd;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return ; // error code
	}
	ft_etc_passwd_loop(vars, str, tmp, fd);
	close (fd);
}

void	ft_home_usr_retrvl(t_vars *vars, char **home, char **usr)
{
	t_kv	*home_env;
	t_kv	*user_env;

	home_env = (ft_val_retrieval(vars, "HOME"));
	if (!home_env)
	{
		*home = "/nfs/homes/";
		user_env = (ft_val_retrieval(vars, "USER"));
		if (user_env)
			*usr = user_env->val;
		else
			*usr = NULL;
	}
	else
	{
		*home = home_env->val;
		*usr = NULL;
	}
}

void	ft_user_home(t_vars *vars, char **str, char **tmp)
{
	char	*home;
	int		len;
	char	*usr;

	ft_home_usr_retrvl(vars, &home, &usr);
	len = ft_strlen(&(*str)[1]);
	*tmp = calloc(len + ft_strlen(home) + ft_strlen(usr) + 1, sizeof(char));
	if (!*tmp)
		ft_exit(vars, MALLOC_ERROR);
	ft_strlcpy(*tmp, home, ft_strlen(home) + 1);
	if (usr)
		ft_strlcat(*tmp, usr, ft_strlen(*tmp) + ft_strlen(usr) + 1);
	ft_strlcat(*tmp, &(*str)[1], len + ft_strlen(home) + 1);
	if (access(*tmp, F_OK))
	{
		free (*tmp);
		*tmp = NULL;
	}
}

void	ft_home_expand(t_vars *vars, char **str)
{
	char	*tmp;

	if ((*str)[0] == '~' && (*str)[1] == '/')
		ft_home(vars, str);
	if ((*str)[0] == '~' && !ft_isdigit((*str)[1]))
	{
		tmp = NULL;
		ft_etc_passwd(vars, str, &tmp);
		if (!tmp)
		{
			ft_user_home(vars, str, &tmp);
		}
		if (tmp)
		{
			free (*str);
			*str = tmp;
		}
	}
}
