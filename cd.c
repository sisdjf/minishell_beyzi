/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/10/02 03:10:14 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_args_cd(t_stock *stock, char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
        i++;
    if(i > 2)
    {
        printf("cd : too many arguments\n");
        return (0);
    }
    return(1);
}

char *find_env_var(t_envp *envp)
{
    t_envp  *tmp;
    
    tmp = envp;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, "HOME"))
            return((tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}




int ft_cd(char **cmd, t_stock *stock)
{
    int ret;
    char *path;

    if(!check_args_cd(stock, cmd))
        return (0);
    if(!cmd[1])
    {
        path = find_env_var(stock->envp);
        if(!path)
            return (0);
    }
    else
            path = cmd[1];
    ret = chdir(path);
    if(ret == -1)
    {
        printf("cd : %s: No such file or directory\n", cmd[1]);
        return (0);
    }
    return (1);   
}

