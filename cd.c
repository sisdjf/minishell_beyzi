/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/10/02 18:17:04 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_args_cd(char **cmd)
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




int ft_cd(t_stock *stock)
{
    int ret;
    char *path;

    if(!check_args_cd(stock->tab))
        return (0);
    if(!stock->tab[1])
    {
        path = find_env_var(stock->envp);
        if(!path)
            return (0);
    }
    else
            path = stock->tab[1];
    ret = chdir(path);
    if(ret == -1)
    {
        printf("cd : %s: No such file or directory\n", stock->tab[1]);
        return (0);
    }
    return (1);   
}

int cd_test(t_stock *stock)
{
    int i = 0;
    while(stock->tab[i])
    {
        if(strcmp(stock->tab[i], "cd") == 0)
        {
            printf("cd  = %s\n", stock->tab[i]);
            ft_cd(stock);
        }
        else
        {
            printf("another builtin\n");
        }
        i++;
    }
    return (0);
}
