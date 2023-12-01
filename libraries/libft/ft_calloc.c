/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:35:17 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/30 16:13:16 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allspc;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && size != 0 && nmemb > (total_size / size))
		return (NULL);
	allspc = malloc(total_size);
	if (allspc == NULL)
		return (NULL);
	ft_bzero(allspc, total_size);
	return (allspc);
}
