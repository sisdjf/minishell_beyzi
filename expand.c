/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/28 00:49:50 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	chr_dollar(t_stock *stock, t_token *token)
{
	int	i;

	i = 0;
	while (token) //->type : cd
	{
		// if (token->type == WORD)
		// {
		// 	while (token->name[i])
		// 	{
		// 		printf("Je suis la : %s\n", token->name);
		// 		i++;
		// 	}
		// }
		if (ft_strchr(token->name, '$'))
		{
			print_envp(stock->env);
			printf("LE DOLLAR: %s\n", token->name);
		}
		// if (ft_strcmp(token->name, "env") == 0)
		// {
		// 	print_envp(stock->env);
		// 	printf("LE ENV: %s\n", token->name);
		// }
		// else
		// {
		// 		printf("ERROR NOT ENV\n");
		// 		return ;
		// }
		token = token->next;
	}
}

// void    ft_expand(char **env)
// {

// }

// ls $OUI | wc

// str = ls
// WORD

// str = $LESS$LOGNAME$HOME
// str = -Rsizitouthome/desktop/here
// WORD

// str = |
// PIPE

// str = wc
// WORD

// ls -R | wc

// str = echo
// WORD

// str = sirine
// WORD