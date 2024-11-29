/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:13 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 01:43:45 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	d_loop_right(t_stock *stock, char *str, int *i, int word)
{
	while (str[(*i)])
	{
		stock->nb_g = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '>')
		{
			stock->nb_g++;
			if (stock->nb_g >= 3)
				return (printf_exit(stock, ERROR_NL, 1));
			(*i)++;
		}
		if (str[*i])
			(*i)++;
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
				&& str[(*i)] != '|'))
		{
			word++;
			(*i)++;
		}
		if (stock->nb_g == 2 && word == 0)
			return (printf_exit(stock, ERROR_NL, 1));
	}
	return (0);
}

int	ft_double_greater_right(t_stock *stock, char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (d_loop_right(stock, str, &i, word))
		return (1);
	if (i > 2 && (str[i - 1] == '>' && str[i - 2] != '>'))
		return (printf_exit(stock, ERROR_NL, 1));
	return (0);
}

int	d_loop_left(t_stock *stock, char *str, int *i, int word)
{
	while (str[(*i)])
	{
		stock->nb_g = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '<')
		{
			stock->nb_g++;
			if (stock->nb_g >= 3)
				return (printf_exit(stock, ERROR_NL, 1));
			(*i)++;
		}
		if (str[*i])
			(*i)++;
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
				&& str[(*i)] != '|'))
		{
			word++;
			(*i)++;
		}
		if (stock->nb_g == 2 && word == 0)
			return (printf_exit(stock, ERROR_NL, 1));
	}
	return (0);
}

int	ft_double_greater_left(t_stock *stock, char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (d_loop_left(stock, str, &i, word))
		return (1);
	if (i > 2 && (str[i - 1] == '<' && str[i - 2] != '<'))
		return (printf_exit(stock, ERROR_NL, 1));
	return (0);
}
