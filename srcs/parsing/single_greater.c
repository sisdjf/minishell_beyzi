/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:07 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 02:53:30 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm_great(char *str, int *word, int *i)
{
	while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
			&& str[(*i)] != '|'))
	{
		(*word)++;
		(*i)++;
	}
}

int	s_loop_right(t_stock *stock, char *str, int *i, int word)
{
	while (str[(*i)])
	{
		stock->nb_g = 0;
		word = 0;
		while (str[(*i)])
		{
			if ((str[*i] == '>' && str[*i + 1] == '<'))
				return (printf_exit(stock, ERROR_NL, 1));
			if ((*i) > 0 && str[(*i)] == '>' && str[(*i) + 1] != '>'
				&& str[(*i) - 1] != '>')
			{
				stock->nb_g++;
				(*i)++;
				break ;
			}
			(*i)++;
		}
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		norm_great(str, &word, i);
		if (stock->nb_g == 1 && word == 0)
			return (printf_exit(stock, ERROR_NL, 1));
	}
	return (0);
}

int	ft_greater_right(t_stock *stock, char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (s_loop_right(stock, str, &i, word))
		return (1);
	if (i > 0 && str[i - 1] == '>')
		return (printf_exit(stock, ERROR_NL, 1));
	return (0);
}

int	s_loop_left(t_stock *stock, char *str, int *i, int word)
{
	while (str[(*i)])
	{
		stock->nb_g = 0;
		word = 0;
		while (str[(*i)])
		{
			if (str[*i] == '<' && str[*i + 1] == '>')
				return (printf_exit(stock, ERROR_NL, 1));
			if ((*i) > 0 && str[(*i)] == '<' && str[(*i) + 1] != '<'
				&& str[(*i) - 1] != '<')
			{
				stock->nb_g++;
				(*i)++;
				break ;
			}
			(*i)++;
		}
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		norm_great(str, &word, i);
		if (stock->nb_g == 1 && word == 0)
			return (printf_exit(stock, ERROR_NL, 1));
	}
	return (0);
}

int	ft_greater_left(t_stock *stock, char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (s_loop_left(stock, str, &i, word))
		return (1);
	if (i > 0 && str[i - 1] == '<')
		return (printf_exit(stock, ERROR_NL, 1));
	return (0);
}
