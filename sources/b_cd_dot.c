/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:10:13 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/08 16:36:04 by thorben          ###   ########.fr       */
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
			i += 1;
        else if (!ft_strncmp(&curpath[i], "/.\0", 3) || !ft_strncmp(&curpath[i], "/\0", 2))
			return (len);
		else
			len++;
	}
	return (len);
}

void	ft_cur_wo_dot(t_vars *vars, char **curpath, int len)
{
	char	*temp;
	int		i;

	temp = (char *)ft_calloc(len, sizeof(char));
	if (!temp)
		ft_exit(vars, MALLOC_ERROR);
	i = -1;
	len = 0;
	while ((*curpath)[++i])
	{
		if (!ft_strncmp(&curpath[0][i], "/./", 3))
		{
			i += 1;
		}
		else if (!ft_strncmp(&curpath[0][i], "/.\0", 3) || !ft_strncmp(&curpath[0][i], "/\0", 2))
			break ;
		else
			temp[len++] = (*curpath)[i];
	}
	temp[len] = '\0';
	free (*curpath);
	*curpath = temp;
}

void	ft_remove_dot(t_vars *vars, char **curpath)
{
	size_t		len;

	len = (ft_remove_dot_counter(*curpath) + 1);
	if (len < ft_strlen(*curpath))
		ft_cur_wo_dot(vars, curpath, len);
}
