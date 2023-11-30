/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:13:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:11:17 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*focc;

	focc = (char *)s;
	while (*focc)
		focc++;
	while (*focc != (char)c && focc > s)
		focc--;
	if (*focc == (char)c)
		return (focc);
	return (NULL);
}
