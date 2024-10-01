/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/01 23:36:15 by sizitout         ###   ########.fr       */
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
			if (stock->envp)
			{
				// ft_expand(stock->envp);
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

void	ft_expand(t_envp *env)
{

	while(env)
	{
		if(ft_strcmp(env->key, env->env_str) == 0)
		{
			printf("%s\n", env->env_str);
			printf("OK OK OK OK OK OK OK OK OK OK\n");
		}
			printf(" JUSTE POUR VOIR %s", env->key);
		env = env->next;	
	}
}
