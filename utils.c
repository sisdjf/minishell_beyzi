/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:52:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/25 17:11:24 by sizitout         ###   ########.fr       */
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
	while (1)
	{
		input = readline("minishell ");
		if (!input)
			return (1);
		add_history(input);
		// printf("%s\n", input);
		if (syntax_error(input))
		{
			free(input);
			return (1);
		}
		ft_token(stock, input);
		chr_dollar(stock->token); //A REVOIRRRRRRRRRR
		//peut etre faire un tmp de l input et peut etre que l input je dois le mettre dans token->cmd
		printf("tt est ok\n");
		free(input);
	}
	return (0);
}


// int	interpret(char *str, char *ptr)
// {
// 	int		i;
// 	int		flag;
// 	char	quote;

// 	i = 0;
// 	flag = 1;
// 	while (str[i] && &str[i] != ptr)
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			flag = -flag;
// 			quote = str[i++];
// 			while (str[i] && &str[i] != ptr && str[i] != quote)
// 				i++;
// 			if (str[i] && &str[i] != ptr && str[i] == quote)
// 				flag = -flag;
// 		}
// 		i++;
// 	}
// 	if (flag < 0)
// 		return (1);
// 	return (0);
// }
