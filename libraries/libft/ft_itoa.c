/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:46:00 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:12:59 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	cnt_num(long int n)
{
	size_t	cnt;

	cnt = 0;
	if (n < 0)
	{
		n *= -1;
		cnt++;
	}
	if (n == 0)
		return (cnt = 1);
	while (n > 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static char	*ft_create_str(size_t cnt, size_t sign, long int n)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (cnt + 1));
	if (str == NULL)
		return (NULL);
	i = cnt;
	str[i--] = '\0';
	if (sign == 1)
	{
		str[0] = '-';
		cnt--;
	}
	while (cnt > 0)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
		cnt--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t		cnt;
	size_t		sign;
	char		*str;
	long int	nl;

	nl = n;
	sign = 0;
	cnt = cnt_num(nl);
	if (nl < 0)
	{
		sign = 1;
		nl *= -1;
	}
	str = ft_create_str(cnt, sign, nl);
	if (!str)
		return (NULL);
	return (str);
}
