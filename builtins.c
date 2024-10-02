/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/10/02 00:44:11 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtins(t_stock *stock, char **envp)
{
    (void)envp;
    t_token *tmp;
    tmp = stock->token;

    while (tmp)
    {
        if (!strcmp(tmp->name, "echo"))
        {
            printf("ECHO TROUVE!\n");
            printf("stock->token->name = %s\n", stock->token->name);
            if (stock->tab == NULL)
                printf("stock->tab is empty, echo a besoin de tableau de chaines e.g. {'echo', '-n', 'lynda'}\n");           
        }
        tmp = tmp->next;
    }
    // cmd --> stock->token->name
    // if(!cmd)
    //     return(0);
    // if(!strcmp(cmd, "echo"))
    //     return (1);
    // else if(!strcmp(cmd, "cd"))
    //     return (1);
    // else if(!strcmp(cmd, "pwd"))
    //     return (1);
    // else if(!strcmp(cmd, "export"))
    //     return (1);
    //  else if(!strcmp(cmd, "unset"))
    //     return (1);
    // else if(!strcmp(cmd, "env"))
    //     return (1);
    // else if(!strcmp(cmd, "exit"))
    //     return (1);
    return (0);           
}