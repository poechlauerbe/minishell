/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:10:13 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/15 13:49:11 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_remove_dot_counter(char *curpath)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	while (curpath[++i])
	{
		if (!ft_strncmp(&curpath[i], "/./", 3))
		{
			len++;
			i += 2;
		}
		else if (!ft_strncmp(&curpath[i], "/.\0", 3))
			return (len);
		else
			len++;
	}
	return (len);
}

void	ft_remove_dot(t_vars *vars, char **curpath)
{
	size_t		len;
	int			i;
	char		*temp;

	len = (ft_remove_dot_counter(*curpath) + 1);
	if (len < ft_strlen(*curpath))
	{
		temp = (char *)ft_calloc(len, sizeof(char));
		if (!temp)
			ft_exit(vars, MALLOC_ERROR);
		i = -1;
		len = 0;
		while ((*curpath)[++i])
		{
			if (!ft_strncmp(&curpath[0][i], "/./", 3))
			{
				temp[len++] = (*curpath)[i];
				i += 2;
			}
			else if (!ft_strncmp(&curpath[0][i], "/.\0", 3))
				break ;
			else
				temp[len++] = (*curpath)[i];
		}
		temp[len] = '\0';
		free (*curpath);
		*curpath = temp;
	}
}
