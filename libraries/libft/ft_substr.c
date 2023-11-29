/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:37:57 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/12 10:45:49 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	if (len > 0)
		ft_strlcpy(ptr, &s[start], len + 1);
	else
		ptr[0] = '\0';
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_substr("hola", 4294967295, 0));
}
 */
