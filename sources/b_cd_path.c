/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:25:06 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_create_full_path(t_vars *vars, char *path, char **cpath)
{
	int		plen;
	int		cplen;
	char	*fpath;

	plen = ft_strlen(path);
	cplen = ft_strlen(*cpath);
	if (path[plen - 1] != '/')
	{
		fpath = (char *)malloc(sizeof(char) * (plen + cplen + 2));
		if (!fpath)
			ft_exit(vars, MALLOC_ERROR, 0);
		ft_strlcpy(fpath, path, (plen + 1));
		ft_strlcat(fpath, "/", (plen + 2));
		ft_strlcat(fpath, *cpath, (plen + cplen + 2));
	}
	else
	{
		fpath = (char *)malloc(sizeof(char) * (plen + cplen + 1));
		if (!fpath)
			ft_exit(vars, MALLOC_ERROR, 0);
		ft_strlcpy(fpath, path, (plen + 1));
		ft_strlcat(fpath, *cpath, (plen + cplen + 1));
	}
	return (fpath);
}

char	*ft_diff_paths(t_vars *vars, char *path, char **curpath)
{
	char	*fpath;

	fpath = ft_create_full_path(vars, path, curpath);
	if (!access(fpath, F_OK))
		return (fpath);
	else
	{
		free (fpath);
		return (NULL);
	}
}

void	ft_check_path_null(t_vars *vars, char **curpath)
{
	char	*fpath;
	int		len;

	len = ft_strlen(*curpath);
	fpath = (char *)malloc(sizeof(char) * (len + ft_strlen(*curpath) + 3));
	if (!fpath)
		ft_exit(vars, MALLOC_ERROR, 0);
	ft_strlcpy(fpath, "./", 3);
	ft_strlcat(fpath, *curpath, (len + ft_strlen(*curpath) + 3));
	free(*curpath);
	*curpath = fpath;
}

void	ft_check_pot_path(t_vars *vars, char **curpath)
{
	char	**cdpath;
	char	*temp;
	int		i;

	temp = NULL;
	cdpath = ft_split(ft_return_val(vars, "CDPATH"), ':');
	i = 0;
	while (cdpath && cdpath[i])
	{
		temp = ft_diff_paths(vars, cdpath[i++], curpath);
		if (temp)
		{
			free (*curpath);
			*curpath = temp;
		}
	}
	if (!temp && ft_strcmp(*curpath, ".") && ft_strcmp(*curpath, ".."))
		ft_check_path_null(vars, curpath);
	i = 0;
	while (cdpath && cdpath[i])
	{
		free (cdpath[i]);
		i++;
	}
	free (cdpath);
}
