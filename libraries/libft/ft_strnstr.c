/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:30:42 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:11:21 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	size_t	lensave;

	if (*little == '\0')
		return ((char *)big);
	while (len && *big != '\0')
	{
		i = 0;
		lensave = len;
		while (big[i] == little[i] && big[i] != '\0' && lensave > 0)
		{
			if (little[i + 1] == '\0')
				return ((char *)big);
			i++;
			lensave--;
		}
		big++;
		len--;
	}
	return (NULL);
}
