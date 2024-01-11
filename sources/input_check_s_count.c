/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_s_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <poechlauerbe@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:52:13 by bpochlau          #+#    #+#             */
/*   Updated: 2024/01/11 17:52:31 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_init_s_count(t_vars *vars, t_prg **temp)
{
	vars->p_start = calloc(1, sizeof(t_prg));
	if (!vars->p_start)
		ft_exit(vars, MALLOC_ERROR);
	vars->p_start->next = NULL;
	vars->p_start->oper = '0';
	*temp = vars->p_start;
	(*temp)->str_c = 0;
	(*temp)->in_file = NULL;
	(*temp)->out_file = NULL;
}

void	ft_space_n_reds_helper(t_vars *vars, char **inp, t_prg **temp)
{
	while (**inp == ' ' || **inp == '\n' || **inp == '\t'
		|| **inp == '\r' || **inp == '\f' || **inp == '\v')
		*inp += 1;
	if ((**inp >= 33 || **inp < 0) && **inp != 127 && **inp != '|'
		&& **inp != '<' && **inp != '>')
	{
		if (((*temp)->oper == '<' || (*temp)->oper == '>'
				|| (*temp)->oper == O_APP_OUT || (*temp)->oper == O_HEREDOC)
			&& (*temp)->str_c == 1)
			ft_new_node(vars, temp, inp);
		(*temp)->str_c += 1;
	}
}

void	ft_check_string_count(t_vars *vars, char *inp)
{
	t_prg	*temp;

	temp = NULL;
	ft_init_s_count(vars, &temp);
	while (*inp)
	{
		ft_space_n_reds_helper(vars, &inp, &temp);
		while (*inp && (*inp >= 33 || *inp < 0) && *inp != 127)
		{
			if (*inp == '\'' || *inp == '\"')
				ft_check_quotes(&inp);
			if (*inp == '|' || *inp == '<' || *inp == '>')
			{
				ft_new_node(vars, &temp, &inp);
				break ;
			}
			if (*inp)
				inp++;
		}
	}
}
