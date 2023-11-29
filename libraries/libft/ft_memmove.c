/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:30:13 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/12 17:08:39 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*destptr;
	const char	*srcptr;

	if (dest == 0 && src == 0)
		return (0);
	i = 0;
	destptr = dest;
	srcptr = src;
	if (srcptr < destptr)
	{
		while (n--)
			destptr[n] = srcptr[n];
	}
	else
	{
		while (i < n)
		{
			destptr[i] = srcptr[i];
			i++;
		}
	}
	return (destptr);
}
/*
int	main(void)
{
	char	str[] ="Was mache ich hier?";
	char	*strptr = &str[6];
	printf("%s, %s\n", str, strptr);
	ft_memmove(str, strptr, 6);
	printf("%s\n", str);
}
*/
