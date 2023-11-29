/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:31:41 by tbenz             #+#    #+#             */
/*   Updated: 2023/10/08 16:30:01 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putptrhelp(unsigned long long nb, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		ft_putptrhelp((nb / 16), len);
	ft_putchar(base[nb % 16], len);
}

void	ft_putptr(void *ptr, int *len)
{
	if (!ptr)
	{
		*len += write(1, "(nil)", 5);
		return ;
	}
	*len += write(1, "0x", 2);
	ft_putptrhelp((unsigned long long)ptr, len);
}
