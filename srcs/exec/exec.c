/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/22 21:36:45 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*chr_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			return (ft_strdup(env[i] + 5));
		}
		i++;
	}
	return (NULL);
}
char	*path_to_cmd(t_exec *exec, char **env)
{
	exec->path = chr_path(env);
	if (exec->path)
	{
		exec->split_path = ft_split(exec->path, ':');
		free(exec->path);
	}
	return (exec->split_path);
}

// void	ft_exec(t_exec *exec, char **env)
// {
// 	path_to_cmd(stock->str, env);
// }
// void    env(t_envp *envp)
// {
//     t_envp	*tmp;

//     tmp = envp;
//     while(tmp)
//     {
//         if(tmp->value)
//             printf("%s=%s\n", tmp->key, tmp->value);
//         tmp = tmp->next;
//     }
// }

// char	*retrouver_variable(t_envp *envp, char *name)
// {
// 	t_envp	*tmp;

//     tmp = envp;
//     while(tmp)
//     {
// 		if (ft_strcmp(tmp->key, name) == 0)
// 			return(tmp->value);
//         tmp = tmp->next;
//     }
// 	return (NULL);
// }
