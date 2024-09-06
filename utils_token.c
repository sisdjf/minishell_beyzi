/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:36:01 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/06 17:51:48 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    ft_(t_token *token, char *input)
// {
//     int i;

//     i = 0;
//    while(input[i])
//    {
//     if()
//     i++;
//    }
//     if(token->type == REDIR_L)
//         if(token->next->type == WORD)
        
//         // if(1 < 0)
     
// }

// apres un chevron CEST FORCEMENT un fichier
// tout ce qui est ni un fichier ni une redirection EST un argument
// le premier argument = la commande
// < FEFEFEF | FEFEF
// -R > avion < ls >> bonjour < echo -s