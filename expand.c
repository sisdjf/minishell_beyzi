/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/24 14:06:53 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FONCTION FAITE LE 21 SEPT A REVOIR

void	chr_word(t_token *token)
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
		if (ft_strchr(token->name,'$'))
		{
			printf("LE DOLLAR: %s\n", token->name);
		}
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