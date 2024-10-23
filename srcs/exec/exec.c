/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/23 20:58:43 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
char	*chr_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH=") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*path_to_cmd(t_exec *exec, t_envp *envp)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	exec->path = chr_path(envp);
	if (exec->path)
	{
		exec->split_path = ft_split(exec->path, ':');
		// free(exec->path);
		i = 0;
		while (exec->split_path[i])
		{
			tmp = ft_strjoin(exec->split_path[i], "/");
			cmd_path = ft_strjoin(tmp, exec->cmd);
			free(tmp);
			printf("path to cmd\n");
			if (access(cmd_path, X_OK) == 0)
			{
				free_split(exec->split_path);
				return (cmd_path);
			}
			free(cmd_path);
			i++;
		}
		free_split(exec->split_path);
	}
	return (NULL);
}

void	ft_exec(t_exec *exec, t_envp *envp)
{
	path_to_cmd(exec, envp);
}
