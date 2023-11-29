/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:48 by bpochlau          #+#    #+#             */
/*   Updated: 2023/11/29 16:21:02 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_check_string(char *inp)
{
	int	strings;
	int	cmds;

	
}

void	ft_check_input(t_vars *vars)
{
	char	*inp;
	int		i;

	inp = vars->inp;
	if (!inp)
		return ;
	while (*inp == ' ' || *inp == '\n' || *inp == '\t'
		|| *inp == '\r' || *inp == '\f' || *inp == '\v')
		inp++;
	while (*inp >= 33 && inp <= 126)
	{
		if (*inp == '|' || *inp == '<' || *inp == '>' )
			break;
		inp++;
	}

}
