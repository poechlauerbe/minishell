/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_dotdot2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorben <thorben@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:41:44 by tbenz             #+#    #+#             */
/*   Updated: 2024/01/08 17:23:19 by thorben          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_dot_dot_len(char *cp, int i)
{
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
