/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:58 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/03 18:23:38 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_quotes(char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (*str == '\'' && double_quote == 0)
		{
			single_quote = !single_quote;
		}
		else if (*str == '"' && single_quote == 0)
		{
			double_quote = !double_quote;
		}
		str++;
	}
	if (single_quote || double_quote)
	{
		printf("Error quote not close\n");
		return (1);
	}
	return (0);
}

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
		while (str[(*i)] && str[(*i)] == ' ')
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
	while (str[i] && str[i] == ' ')
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
void	ft_positif(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] < 0)
			input[i] = -input[i];
		i++;
	}
}
// syntax errors
int	syntax_error(char *input)
{
	if (ft_quotes(input)) return (1);
	/*expend*/
	ft_negatif(input);
	if (ft_pipe(input))
		return (1);
	if (ft_greater_right(input))
		return (1);
	if (ft_greater_left(input))
		return (1);
	if (ft_double_greater_right(input))
		return (1);
	if (ft_double_greater_left(input))
		return (1);
	ft_positif(input);
	return (0);
}
