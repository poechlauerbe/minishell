/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 16:15:12 by tbenz             #+#    #+#             */
/*   Updated: 2023/10/08 16:29:15 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_check_prntf(char s, int *len, va_list *args)
{
	if (s == 'c')
		ft_putchar(va_arg(*args, int), len);
	else if (s == 's')
		ft_putstr(va_arg(*args, char *), len);
	else if (s == 'p')
		ft_putptr(va_arg(*args, void *), len);
	else if (s == 'd' || s == 'i')
		ft_putnbr(va_arg(*args, int), len);
	else if (s == 'u')
		ft_putuns(va_arg(*args, unsigned int), len);
	else if (s == 'x' || s == 'X')
		ft_puthex(s, va_arg(*args, unsigned), len);
	else if (s == '%')
		*len += write (1, "%", 1);
	else
		return ;
}

int	ft_printf(const char *s, ...)
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
			ft_check_prntf(*(++s), &len, &args);
		}
		else
			len += write(1, &s[0], 1);
		s++;
	}
	va_end(args);
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	int		len1 = 0;
	int		len2 = 0;
	void	*ptr;

	ptr = &len1;
	len1 = ft_printf("normal string\t");
	len2 = printf("normal string\n");
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);

	len1 = ft_printf("nor%%mal \t");
	len2 = printf("nor%%mal\n");
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);

	len1 = ft_printf("nasdf %s\t", "das ist ein String");
	len2 = printf("nasdf %s\n", "das ist ein String");
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);

	len1 = ft_printf("nasdf %p\t", ptr);
	len2 = printf("nasdf %p\n", ptr);

	len1 = ft_printf("nasdf %p\t, %s", ptr, "asdsdgfdsfa");
	len2 = printf("nasdf %p\t, %s\n", ptr, "asdfa");
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);

	len1 = ft_printf(" NULL %s NULL ", NULL);
	len2 = printf(" NULL %s NULL ", NULL);
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);

	len1 = ft_printf(" %% ");
	len2 = printf(" %% ");
	printf("ft_printf len: %d\tprintf len: %d\n", len1, len2);
}
*/
