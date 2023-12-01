/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:19:16 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:12:46 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*chrptr;
	size_t	i;

	i = 1;
	chrptr = (char *)s;
	while (i < n && *chrptr != (char)c)
	{
		chrptr++;
		i++;
	}
	if (*chrptr == (char)c && n > 0)
		return (chrptr);
	return (NULL);
}
