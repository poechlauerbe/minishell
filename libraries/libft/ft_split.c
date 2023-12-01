/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:51:44 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:11:55 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_str_count(char const *s, char c)
{
	size_t	arr_cnt;

	arr_cnt = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s != c)
			arr_cnt++;
		while (*s != c && *s)
			s++;
		while (*s == c && *s)
			s++;
	}
	return (arr_cnt);
}

static void	ft_free(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(arr[j++]);
	free (arr);
}

static char	**ft_arrgen(char const *s, char c, char **arr)
{
	int		i;
	size_t	len;

	i = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			len = 0;
			while (*s != c && *s && ++len)
				s++;
			arr[i++] = ft_substr(s - len, 0, len);
			if (arr[i - 1] == NULL)
			{
				ft_free(arr, i);
				return (NULL);
			}
		}
		if (*s)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **)malloc((ft_str_count(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_arrgen(s, c, arr);
	if (!arr)
		return (NULL);
	return (arr);
}
