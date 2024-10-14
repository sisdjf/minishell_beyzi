/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:58:44 by lybey             #+#    #+#             */
/*   Updated: 2024/10/11 18:00:15 by lybey            ###   ########.fr       */
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

char    *get_key_export(char *str)
{
    int i;

    i = 0;
    
    while(str[i])
    {
        if(str[i] == '=')
            return (ft_substr(str, 0, i ));
        i++;
    }
    return (strdup(str));
}
char    *get_value_export(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return (ft_strdup(str + i + 1));
        i++;
    }
    return (NULL);
}

int add_to_env(char *key, char *value, t_envp *envp)
{
    int     i;
    char    *str;
    char    *mini;
    t_envp  *to_replace;
    
    i = 0;
    if (!key[i] || (!ft_isalnum(key[i]) && key[i] != '_'))
        return (printf("bash: export: `%s': not a valid identifier\n",key), 1);
    while(key[i])
    {
        if (ft_isalnum(key[i]) || key[i] == '_')
            i++;
        else
            return (printf("bash: export:`%s': not a valid idetifier\n", key), 1);
    }
    to_replace = search_envp(envp, key);
    if (to_replace && value)
    {
        free(to_replace->value);
        to_replace->value = value;
    }   
    else if(!to_replace)
    {
        str = ft_strjoin(key, "=");
        mini = ft_strjoin(str, value);
        free(value);
        free(str);
        ft_lstadd_back_envp(&envp, ft_lstnew_envp(mini));
    }
    return (0);
}

int export(char **cmd, t_envp *envp)
{
    char *key;
    char *value;
    int       i;
    
    i = 1;
    while(cmd[i])
    {
        key = get_key_export(cmd[1]);
        value = get_value_export(cmd[1]);
        add_to_env(key, value, envp);
        free(key);
        i++;
    }
    return (0);
}