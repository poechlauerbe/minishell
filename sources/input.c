/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:30:48 by bpochlau          #+#    #+#             */
/*   Updated: 2023/12/11 17:49:28 by bpochlau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_input_strlen(char **inp)
{
	int		strlen;
	char	*temp;

	strlen = 0;
	if (!*inp && !**inp)
		return (strlen);
	while (**inp == ' ' || **inp == '\n' || **inp == '\t'
		|| **inp == '\r' || **inp == '\f' || **inp == '\v'
		|| **inp == '|' || **inp == '<' || **inp == '>')
		*inp += 1;
	temp = *inp;
	while (*temp >= 33 && *temp <= 126 && *temp != '|')
	{
		// if (*temp == '<' || *temp == '>' )
		// 	break;
		if (*temp == '\'')
		{
			while (*temp)
			{
				temp++;
				strlen++;
				if (*temp == '\'')
					break ;
			}
			// if (*temp == '\0')
			// 	return (OPEN_QUOTES);
		}
		if (*temp == '\"')
		{
			while (*temp)
			{
				temp++;
				strlen++;
				if (*temp == '\"')
					break ;
			}
			// if (*temp == '\0')
			// 	return (OPEN_QUOTES);
		}
		strlen++;
		temp++;
	}
	return (strlen);
}

void	ft_malloc_prog_2d_str(t_vars *vars)
{
	char	**prog;
	char	*str;
	char	*inp;
	int		strlen;
	int		i;
	t_prg	*temp;

	inp = vars->inp;
	temp = vars->p_start;
	while (temp)
	{
		prog = ft_calloc(temp->str_c + 1, sizeof(char *));
		if (!prog)
			ft_exit(vars, MALLOC_ERROR);
		i = 0;
		if (*inp == '|')
			inp++;
		while (i < temp->str_c)
		{
			strlen = ft_input_strlen(&inp);
			str = malloc((strlen + 1) * sizeof(char));
			if (!str)
				ft_exit(vars, MALLOC_ERROR);
			ft_strlcpy(str, inp, strlen + 1);
			prog[i] = str;
			inp += strlen;
			i++;
		}
		prog[i] = NULL;
		temp->prog = prog;
		temp = temp->next;
	}
}

void	ft_check_string_count(t_vars *vars, char *inp)
{
	t_prg	*temp;

	// if (!inp || !*inp)
	// 	ft_reset();
	vars->p_start = malloc(sizeof(t_prg));
	if (!vars->p_start)
		ft_exit(vars, MALLOC_ERROR);
	vars->p_start->next = NULL;
	vars->p_start->oper = '0';
	temp = vars->p_start;
	temp->str_c = 0;
	temp->in_file = NULL;
	temp->out_file = NULL;
	while (*inp)
	{
		while (*inp == ' ' || *inp == '\n' || *inp == '\t'
			|| *inp == '\r' || *inp == '\f' || *inp == '\v')
			inp++;
		if (*inp >= 33 && *inp <= 126 && *inp != '|' && *inp != '<' && *inp != '>')
		{
			if ((temp->oper == '<' || temp->oper == '>') && temp->str_c == 1)
				ft_new_node(vars, &temp, &inp);
			temp->str_c += 1;
		}
		while (*inp >= 33 && *inp <= 126)
		{
			if (*inp == '\'' || *inp == '\"')
				ft_check_quotes(&inp);
			if (*inp == '|' || *inp == '<' || *inp == '>')
			{
				ft_new_node(vars, &temp, &inp);
				break ;
			}
			inp++;
		}
	}
}

void	ft_red_file(t_vars *vars, t_prg *lst)
{
	t_prg	*prog;
	t_prg	*temp;

	temp = lst;
	while (lst)
	{
		prog = NULL;
		if (temp->oper == '|')
		{
			prog = temp;
			temp =temp->next;
			lst = temp;
		}
		while (temp && temp->oper != '|')
		{
			if (temp->oper == '0')
			{
				if (prog == NULL)
					prog = temp;
				// else
				// 	APPEND PROG STRING
			}
			temp = temp->next;
		}
		temp = lst;
		while (temp && temp->oper != '|')
		{
			if (temp->oper == '>' || temp->oper == O_APP_OUT)
				ft_red_new_node(vars, &prog->out_file, temp->prog[0], temp->oper);
			else if (temp->oper == '<')
				ft_red_new_node(vars, &prog->in_file, temp->prog[0], temp->oper);
			temp = temp->next;
		}
		lst = temp;
	}
}

void	ft_check_input(t_vars *vars)
{
	ft_check_string_count(vars, vars->inp);
	ft_malloc_prog_2d_str(vars);
	ft_cleanup_lst(vars);
	ft_red_file(vars, vars->p_start);
	ft_cleanup_reds(vars);
	ft_pipecount(vars);
}
