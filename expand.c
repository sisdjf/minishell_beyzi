/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/28 16:14:15 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chr_dollar(t_stock *stock, t_token *token)
{
	int	i;

	i = 0;
	while (token) //->type : cd
	{
		if (ft_strchr(token->name, '$'))
		{
			if (stock->env)
			{
				stock_env_lst(stock->env, stock);
				// print_lst_envp(stock);
				printf("LE DOLLAR: %s\n", token->name);
			}
			// print_envp(stock->env);
		}
		token = token->next;
	}
}
// void	print_envp(char **env)
// {
// 	int i = 0;
// 	while (env[i])
// 	{
// 		printf("%s\n", env[i]);
// 		i++;
// 	}
// }