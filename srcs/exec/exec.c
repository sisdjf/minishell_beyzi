/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/27 01:42:29 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*chr_path(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			// printf("%s\n", tmp->key);
			return (tmp->value);
		}
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
	printf("exec->cmd = '%s\n", exec->cmd);
	i = -1;
	if (exec->path)
	{
		exec->split_path = ft_split(exec->path, ':');
		// if (exec->split_path)
		// {
		// 	while (exec->split_path[++i])
		// 		printf("%s\n", exec->split_path[i]);
		// }
		i = 0;
		while (exec->split_path[i])
		{
			tmp = ft_strjoin(exec->split_path[i], "/");
			cmd_path = ft_strjoin(tmp, exec->cmd);
			// printf("%s\n", cmd_path);
			free(tmp);
			if (access(cmd_path, X_OK) == 0)
			{
				free_split(exec->split_path);
				return (cmd_path);
			}
			free(cmd_path);
			i++;
		}
	}
	free_split(exec->split_path);
	return (NULL);
}

char	**tab_env(t_exec *exec, t_envp *envp)
{
	int		i;
	int		size;
	char	**env;
	t_envp	*tmp;

	(void)exec;
	tmp = envp;
	i = 0;
	size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	while (envp)
	{
		env[i] = ft_strdup(envp->env_str);
		if (!env)
			return (NULL);
		envp = envp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_exec(t_exec *exec, t_envp *envp, char **cmd)
{
	int		i;
	
	i = 0;
	exec->path = path_to_cmd(exec, envp);
	printf("exec cmd = %s\n", cmd[0]);
	exec->env = tab_env(exec, envp);
	printf("exec path found = %s\n", exec->path);
	while (exec->env[i])
	{
		printf("%s\n", exec->env[i]);
		i++;
	}
	// execve(path, cmd, env);
	if (exec->path)
		return ;
	// printf("CHemin: %s\n", tmp);
	// else
	// 	printf("Erreur : exec->path est NULL.\n");
}