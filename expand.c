/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/02 01:59:55 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chr_dollar(t_stock *stock, t_token *token)
{
	int		i;
	char	*pos_dollar;
	char	*key_start;
	char	*end;

	i = 0;
	while (token) //->type : cd
	{
		pos_dollar = ft_strchr(token->name, '$');
		if (pos_dollar)
		{
			key_start = pos_dollar + 1;
			end = key_start;
			while (*end && (ft_isalnum(*end) || *end == '_'))
			{
				end++;
			}
			*end = '\0';
			ft_expand(stock->envp, key_start);
			// if (stock->envp)
			// {
			// 	ft_expand(stock->envp,);
			// 	printf("LE DOLLAR: %s\n", token->name);
			// }
		}
		token = token->next;
	}
}

void	ft_expand(t_envp *env, char *key_start)
{
	while (env)
	{
		if (ft_strcmp(env->key, key_start) == 0)
		{
			if (env->value)
			{
				printf("%s\n", env->value);
			}
			else
			{
				printf("La clé $%s existe mais n'a pas de valeur.\n",
						key_start);
			}
			return ;
		}
		env = env->next;
	}
}
