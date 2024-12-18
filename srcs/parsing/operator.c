/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:58 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/22 21:12:33 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	loop_pipe(char *str, int *i, int nb_pipe, int word)
{
	while (str[(*i)])
	{
		nb_pipe = 0;
		word = 0;
		while (str[(*i)] && str[(*i)] == '|')
		{
			nb_pipe++;
			(*i)++;
		}
		if (nb_pipe > 1 || (nb_pipe == 1 && word == 0 && str[(*i)] == '\0'))
			return (printf(ERROR_PIPE_MSG), 1);
		while (str[(*i)] && (str[(*i)] == ' ' || str[(*i)] == '\t'))
			(*i)++;
		while (str[(*i)] && str[(*i)] != '|')
		{
			word++;
			(*i)++;
		}
		if (nb_pipe == 1 && word == 0)
			return (printf(ERROR_PIPE_MSG), 1);
	}
	return (0);
}

int	ft_pipe(char *str)
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
		return (printf(ERROR_PIPE_MSG), 1);
	if (loop_pipe(str, &i, nb_pipe, word))
		return (1);
	if (str[i - 1] == '|')
		return (printf(ERROR_PIPE_MSG), 1);
	return (0);
}

void	ft_negatif(char *input)
{
	int		i;
	char	j;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			j = input[i++];
			while (input[i] != j)
			{
				input[i] = -input[i];
				i++;
			}
		}
		i++;
	}
}

char	*ft_positif(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] < 0)
			input[i] *= -1;
		i++;
	}
	return (input);
}

int	syntax_error(char *input)
{
	if (ft_quotes(input))
		return (1);
	ft_negatif(input);
	if (ft_pipe(input))
		return (1);
	if (ft_greater_right(input))
	{
		return (1);
	}
	else if (ft_greater_left(input))
	{
		return (1);
	}
	if (ft_double_greater_right(input))
	{
		return (1);
	}
	if (ft_double_greater_left(input))
	{
		return (1);
	}
	ft_positif(input);
	return (0);
}
