/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dotdot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:28:33 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 13:02:14 by tbenz            ###   ########.fr       */
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

	if (i == 1)
		return (0);
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

void	ft_create_cp2(char **cp, int cl, int i, char **tmp)
{
	int	j;
	int	k;

	k = -1;
	while ((*cp)[++k] && k < (i - cl))
		(*tmp)[k] = (*cp)[k];
	j = 3;
	i += j;
	while ((*cp)[i])
	{
		(*tmp)[k++] = (*cp)[i];
		i++;
	}
	(*tmp)[k] = '\0';
}

void	ft_create_cp(t_vars *vars, char **cp, int i, int cl)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(*cp) - cl - ft_dot_dot_len(*cp, i);
	if (i == 1)
	{
		len = ft_dot_dot_len(*cp, 0);
		if (len == ft_strlen(*cp))
			temp = ft_substr(*cp, 0, 1);
		else
			temp = ft_substr(*cp, (len - 1), ft_strlen(*cp));
	}
	else
		temp = (char *)ft_calloc((len + 1), sizeof(char));
	if (!temp)
		ft_exit(vars, MALLOC_ERROR);
	if (i > 3)
		ft_create_cp2(cp, cl, i, &temp);
	free (*cp);
	*cp = temp;
}

int	ft_remove_dot_dot(t_vars *vars, char **cp)
{
	int	curr_len;
	int	i;

	i = -1;
	while ((*cp)[++i])
	{
		if ((*cp)[i] == '.' && (*cp)[i + 1] == '.' &&
			((*cp)[i + 2] == '/' || (*cp)[i + 2] == '\0'))
		{
			if (ft_test_dir(vars, cp, i))
				return (1);
			ft_create_cp(vars, cp, i, curr_len);
			i = 0;
		}
		if (i == 0 || (*cp)[i - 1] == '/')
			curr_len = ft_remove_dd_currlen(*cp, i);
	}
	return (0);
}
