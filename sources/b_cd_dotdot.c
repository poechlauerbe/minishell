/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dotdot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:28:33 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/14 18:53:42 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_remove_dd_currlen(char *cp, int i)
{
	int	len;

	len = 0;
	while (cp[i] && cp[i] != '/')
	{
		len++;
		i++;
	}
	while (cp[i++] == '/')
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
	while (++j < i)
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

void	ft_create_cp2(char **cp, int cl, int i, char **tmp)
{
	int	j;
	int	k;

	k = -1;
	j = ft_dot_dot_len(*cp, i);
	while ((*cp)[++k] && k <= (i - cl))
		(*tmp)[k] = (*cp)[k];
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
	char	*temp;

	i = 0;
	while (cp[0][i + 1] == '/')
		i++;
	temp = ft_substr(*cp, i, (ft_strlen(*cp) - i));
	if (!temp)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	while ((temp)[++i])
	{
		if (!ft_strncmp(&temp[i], "/../", 4) ||
			!ft_strncmp(&temp[i], "/..\0", 4))
		{
			if (ft_test_dir(vars, &temp, i))
				return (1);
			ft_create_cp(vars, &temp, i, curr_len);
			i = 0;
		}
		if (i == 0 || (temp)[i - 1] == '/')
			curr_len = ft_remove_dd_currlen(temp, i);
	}
	free (*cp);
	*cp = temp;
	return (0);
}
