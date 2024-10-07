/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:58:44 by lybey             #+#    #+#             */
/*   Updated: 2024/10/04 18:04:24 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void    print_export(t_envp *envp)
{
    t_envp  *tmp;
    
    tmp = envp;
    while(tmp)
    {
        if(!(tmp->value))
            printf("export %s\n", tmp->key);
        else
            printf("export %s=\"%s\"\n", tmp->key, tmp->value);
        tmp = tmp->next;      
    }
}

// char    get_key_export(char **cmd)
// char    get_value_export(char **cmd)

int export(char **cmd, t_envp *envp)
{
    char    *key;
    char    *value;
    int     nb_cmd;
    int     i;
}