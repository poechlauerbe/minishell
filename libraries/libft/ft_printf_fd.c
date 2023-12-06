/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:15:12 by tbenz             #+#    #+#             */
/*   Updated: 2023/12/06 17:17:24 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_pffd(char *s, int *len, int fd)
{
	if (!s)
	{
		*len += write(fd, "(null)", 6);
		return ;
	}
	while (*s)
	{
		ft_putchar(*s, len);
		s++;
	}
}

void	ft_putchar_pffd(int c, int *len, int fd)
{
	*len += write(fd, &c, 1);
}

void	ft_check_prntffd(char s, int *len, va_list *args, int fd)
{
	if (s == 'c')
		ft_putchar_pffd(va_arg(*args, int), len, fd);
	else if (s == 's')
		ft_putstr_pffd(va_arg(*args, char *), len, fd);
	else if (s == 'p')
		ft_putptr_pffd(va_arg(*args, void *), len, fd);
	else if (s == 'd' || s == 'i')
		ft_putnbr_pffd(va_arg(*args, int), len, fd);
	else if (s == 'u')
		ft_putuns_pffd(va_arg(*args, unsigned int), len, fd);
	else if (s == 'x' || s == 'X')
		ft_puthex_pffd(s, va_arg(*args, unsigned), len, fd);
	else if (s == '%')
		*len += write (fd, "%", 1);
	else
		return ;
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	int		len;
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	len = 0;
	while (*s)
	{
		if (*s == '%')
		{
			ft_check_prntffd(*(++s), &len, &args, fd);
		}
		else
			len += write(fd, &s[0], 1);
		s++;
	}
	va_end(args);
	return (len);
}
