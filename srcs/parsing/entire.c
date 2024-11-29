/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entire.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:36:35 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 01:38:42 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
