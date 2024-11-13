/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:07 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/12 19:52:02 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	norm_great(char *str, int word, int *i)
{
	while (str[(*i)] && (str[(*i)] != '>' && str[(*i)] != '<'
			&& str[(*i)] != '|'))
	{
		word++;
		(*i)++;
	}
}

int	s_loop_right(char *str, int *i, int nb_greater, int word)
{
	while (str[(*i)])
	{
		nb_greater = 0;
		word = 0;
		while (str[(*i)])
		{
			if ((*i) > 0 && str[(*i)] == '>' && str[(*i) + 1] != '>' && str[(*i)
				- 1] != '>')
			{
				nb_greater++;
				break ;
			}
			(*i)++;
		}
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		norm_great(str, word, i);
		if (nb_greater == 1)
			break ;
		if (nb_greater == 1 && word == 0)
			return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	ft_greater_right(char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (s_loop_right(str, &i, nb_greater, word))
		return (1);
	if (i > 0 && str[i - 1] == '>')
	{
		return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	s_loop_left(char *str, int *i, int nb_greater, int word)
{
	while (str[(*i)])
	{
		nb_greater = 0;
		word = 0;
		while (str[(*i)])
		{
			if ((*i) > 0 && str[(*i)] == '<' && str[(*i) + 1] != '<' && str[(*i)
				- 1] != '<')
			{
				nb_greater++;
				break ;
			}
			(*i)++;
		}
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		norm_great(str, word, i);
		if (nb_greater == 1)
			break ;
		if (nb_greater == 1 && word == 0)
			return (printf(ERROR_NL), 1);
	}
	return (0);
}

int	ft_greater_left(char *str)
{
	int	i;
	int	nb_greater;
	int	word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (s_loop_left(str, &i, nb_greater, word))
		return (1);
	if (i > 0 && str[i - 1] == '<')
	{
		return (printf(ERROR_NL), 1);
	}
	return (0);
}
