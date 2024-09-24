/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:43:13 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/19 18:02:19 by lybey            ###   ########.fr       */
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
			{
				printf("A\n");
				return (printf(ERROR_NL), 1);
			}
			(*i)++;
		}
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
		{
			printf("B\n");
			return (printf(ERROR_NL), 1);
		}
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
	if (str[i - 1] == '>' && str[i - 2] != '>')
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
			{
				printf("C\n");
				return (printf(ERROR_NL), 1);
			}
			(*i)++;
		}
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
		{
			printf("D\n");
			return (printf(ERROR_NL), 1);
		}
	}
	return (0);
}

int	ft_double_greater_left(char *str)
{
	int i;
	int nb_greater;
	int word;

	i = 0;
	word = 0;
	nb_greater = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (d_loop_left(str, &i, nb_greater, word))
		return (1);
	if (str[i - 1] == '<' && str[i - 2] != '<')
	{
		printf("F\n");
		return (printf(ERROR_NL), 1);
	}
	return (0);
}