/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:05:27 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/15 23:06:24 by sizitout         ###   ########.fr       */
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
