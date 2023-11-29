/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:13:48 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/13 10:03:31 by tbenz            ###   ########.fr       */
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

/* int	main(void)
{
	char	*str1;

	str1 = "Was machst dum da?";
	printf("%s 213421", ft_strrchr(str1, 'd' + 256));
} */
