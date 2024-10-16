/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:55:07 by lybey             #+#    #+#             */
/*   Updated: 2024/10/17 00:20:22 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    env(t_envp *envp)
{
    t_envp  *tmp;

    tmp = envp;
    while(tmp)
    {
        if(tmp->value)
            printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}