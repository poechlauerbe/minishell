/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:31:42 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/07 09:44:11 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*focc;

	focc = (char *)s;
	while (*focc != (char)c && *focc != '\0')
		focc++;
	if (*focc == (char)c)
		return (focc);
	return (NULL);
}

/* int	main(void)
{
	char	*str1;

	str1 = "Was machst dum da?";
	printf("%s 213421", ft_strchr(str1, 'c' + 256));

} */
