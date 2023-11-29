/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:14:49 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/12 10:04:16 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	char str[] = "Was machst du?";
    ft_memset(str, 88, 8);
    printf("%s", str);
    return 0;
}
*/
