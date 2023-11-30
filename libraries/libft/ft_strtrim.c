/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:50:13 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:11:14 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (0);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && *s1)
		start++;
	while (ft_strchr(set, s1[end]) && end > start)
		end--;
	if (start > end)
		ptr = ft_substr(s1, start - 1, 1);
	ptr = ft_substr(s1, start, (end - start + 1));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
