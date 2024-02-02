/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_home2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:37:46 by tbenz             #+#    #+#             */
/*   Updated: 2024/02/02 13:56:08 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_etc_arr_free(char ***arr, char **line)
{
	int		i;

	i = 0;
	while ((*arr)[i])
	{
		free ((*arr)[i]);
		i++;
	}
	free (*arr);
	if (*line)
		free (*line);
}

void	ft_etc_passwd_loop(t_vars *vars, char **str, char **tmp, int fd)
{
	char	*line;
	char	**arr;

	line = get_next_line(fd);
	while (line && !*tmp)
	{
		arr = ft_split(line, ':');
		if (!arr)
			ft_exit(vars, MALLOC_ERROR, 0);
		if (!ft_strcmp(&(*str)[1], arr[0]))
		{
			*tmp = ft_strdup(arr[5]);
			if (!*tmp)
				ft_exit(vars, MALLOC_ERROR, 0);
		}
		ft_etc_arr_free(&arr, &line);
		line = get_next_line(fd);
	}
	if (line)
		free (line);
}
