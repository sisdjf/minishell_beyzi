/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:52:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/28 01:09:13 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_prompt(t_stock *stock, char *input)
{
	// (void)stock;
	while ((input = readline("minishell ")) != NULL)
	{
		if (!input)
			return (1);
		add_history(input);
		// printf("%s\n", input);
		if (syntax_error(input))
		{
			free(input);
			return (1);
		}
		free_tokens(stock->token);
		stock->token = NULL;
		if (ft_token(stock, input) != 0)
		{
			free(input);
			return (1);
		}
		// stock_env_lst(stock->env, stock);
		chr_dollar(stock, stock->token); //A REVOIRRRRRRRRRR
		printf("tt est ok\n");
		free(input);
	}
	return (0);
}