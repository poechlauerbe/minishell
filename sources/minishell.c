/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:33:20 by tbenz             #+#    #+#             */
/*   Updated: 2023/11/28 15:58:41 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char *input;
	ft_handle_singals()
	while (1)
	{
		input = readline("Prompt> $");
		if(ft_strlen(input) > 0)
			add_history(input);
		if(ft_strcmp("input", "cd", 3) == 0)
			printf("%s", getcwd());
	}
}
