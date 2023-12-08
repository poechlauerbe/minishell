/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:01:14 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 17:21:35 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putptrhelp_pffd(unsigned long long nb, int *len, int fd)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		ft_putptrhelp_pffd((nb / 16), len, fd);
	ft_putchar_pffd(base[nb % 16], len, fd);
}

void	ft_putptr_pffd(void *ptr, int *len, int fd)
{
	if (!ptr)
	{
		*len += write(fd, "(nil)", 5);
		return ;
	}
	*len += write(fd, "0x", 2);
	ft_putptrhelp_pffd((unsigned long long)ptr, len, fd);
}

void	ft_putnbr_pffd(int n, int *len, int fd)
{
	long int	i;

	i = n;
	if (i < 0)
	{
		ft_putchar('-', len);
		i *= -1;
	}
	if (i > 9)
	{
		ft_putnbr_pffd(i / 10, len, fd);
		ft_putnbr_pffd(i % 10, len, fd);
	}
	else
		ft_putchar_pffd(i + 48, len, fd);
}

void	ft_putuns_pffd(unsigned int n, int *len, int fd)
{
	if (n >= 10)
		ft_putuns_pffd((n / 10), len, fd);
	ft_putchar_pffd(n % 10 + '0', len, fd);
}

void	ft_puthex_pffd(char s, unsigned int nbr, int *len, int fd)
{
	char	*base;

	if (s == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr >= 16)
		ft_puthex_pffd(s, (nbr / 16), len, fd);
	ft_putchar_pffd(base[nbr % 16], len, fd);
}
