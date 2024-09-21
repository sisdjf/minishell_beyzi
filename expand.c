/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/21 23:49:18 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FONCTION FAITE LE 21 SEPT A REVOIR

void	chr_word(t_token *token)
{
	int i = 0;
	while (token && token->type == WORD) //->type : cd 
	{
		while (token->name[i])
        {
            printf("Je suis la : %s\n", token->name);
            i++;
        }
            
        token->type = WORD;
        printf("L expand : %d\n", token->type);
        i++;
		break;
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