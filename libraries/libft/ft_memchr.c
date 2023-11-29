/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:19:16 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/12 16:58:47 by tbenz            ###   ########.fr       */
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
/*
#include <stdio.h>
int	main(void)
{
	int	tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	printf("%s", (char *)ft_memchr(tab, -1, 7));
}
 */
