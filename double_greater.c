/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:13 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/15 23:15:14 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	d_loop_right(char *str, int *i, int nb_greater, int word)
{
	while (str[(*i)])
	{
		nb_greater = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '>')
		{
			nb_greater++;
			if (nb_greater >= 3)
				return (printf(ERROR_NL), 1);
			(*i)++;
		}
		if (str[*i])
			(*i)++;
		while (str[(*i)] && str[(*i)] == ' ')
			(*i)++;
		while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
				&& str[(*i)] != '|'))
		{
			word++;
			(*i)++;
		}
		if (nb_greater == 1 && word == 0)
			return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	ft_double_greater_right(char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (d_loop_right(str, &i, nb_greater, word))
		return (1);
	if (i > 2 && (str[i - 1] == '>' && str[i - 2] != '>'))
	{
		printf("E\n");
		return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	d_loop_left(char *str, int *i, int nb_greater, int word)
{
	while (str[(*i)])
	{
		nb_greater = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '<')
		{
			nb_greater++;
			if (nb_greater >= 3)
				return (printf(ERROR_NL), 1);
			(*i)++;
		}
		if (str[*i])
			(*i)++;
		while (str[(*i)] && str[(*i)] == ' ')
			(*i)++;
		while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
				&& str[(*i)] != '|'))
		{
			word++;
			(*i)++;
		}
		if (nb_greater == 1 && word == 0)
			return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	ft_double_greater_left(char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (d_loop_left(str, &i, nb_greater, word))
		return (1);
	if (i > 2 && (str[i - 1] == '<' && str[i - 2] != '<'))
	{
		printf("F\n");
		return (printf(ERROR_NL), 1);
	}
	return (0);
}
