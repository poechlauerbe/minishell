/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dotdot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:28:33 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/13 18:03:48 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
