/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:58 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 01:43:04 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	loop_pipe(t_stock *stock, char *str, int *i, int word)
{
	while (str[(*i)])
	{
		stock->nb_pipe = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '|')
		{
			stock->nb_pipe++;
			(*i)++;
		}
		if (stock->nb_pipe > 1 || (stock->nb_pipe == 1 && word == 0
				&& str[(*i)] == '\0'))
			return (printf_exit(stock, ERROR_PIPE_MSG, 1));
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		while (str[(*i)] && str[(*i)] != '|')
		{
			word++;
			(*i)++;
		}
		if (stock->nb_pipe == 1 && word == 0)
			return (printf_exit(stock, ERROR_PIPE_MSG, 1));
	}
	return (0);
}

int	ft_pipe(t_stock *stock, char *str)
{
	int	i;
	int	nb_pipe;
	int	word;

	i = 0;
	word = 0;
	nb_pipe = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '|')
		return (printf_exit(stock, ERROR_PIPE_MSG, 1));
	if (loop_pipe(stock, str, &i, word))
		return (1);
	if (str[i - 1] == '|')
		return (printf_exit(stock, ERROR_PIPE_MSG, 1));
	return (0);
}

int	special_technick(t_stock *stock, char *str)
{
	int	i;

	i = ft_strlen(str);
	i--;
	while (i > 0)
	{
		while (str[i] == ' ' || str[i] == '\t')
			i--;
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			return (printf_exit(stock, ERROR_NL, 1));
		else
			return (0);
		i--;
	}
	return (0);
}

int	syntax_error(t_stock *stock, char *input)
{
	if (ft_quotes(input))
		return (1);
	ft_negatif(input);
	if (ft_pipe(stock, input))
		return (1);
	if (ft_greater_right(stock, input))
		return (1);
	else if (ft_greater_left(stock, input))
		return (1);
	if (ft_double_greater_right(stock, input))
		return (1);
	if (ft_double_greater_left(stock, input))
		return (1);
	if (special_technick(stock, input))
		return (1);
	ft_positif(input);
	return (0);
}
