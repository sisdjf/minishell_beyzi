/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:17:43 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 02:59:19 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*path_to_cmd(t_stock *stock, t_exec *exec, t_envp *envp)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	if (ft_strchr(exec->cmd, '/'))
	{
		if (access(exec->cmd, F_OK | X_OK) != 0)
			return (fprintf(stderr, "ERROR KHALID YOUHOU\n"),
					ft_strdup(exec->cmd));
		return (ft_strdup(exec->cmd));
	}
	exec->path = chr_path(stock, envp);
	i = -1;
	if (!exec->path)
	{
		stock->exit_status = 127;
		return (NULL);
	}
	exec->split_path = ft_split(exec->path, ':');
	i = 0;
	while (exec->split_path[i])
	{
		tmp = ft_strjoin(exec->split_path[i], "/");
		cmd_path = ft_strjoin(tmp, exec->cmd);
		if (!cmd_path)
		{
			free(exec->split_path);
			free(cmd_path);
			free(tmp);
			return (NULL);
		}
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			free_split(exec->split_path);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_split(exec->split_path);
	return (NULL);
}

// void	print_vraitab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// }

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
	env = ft_calloc(size + 1, sizeof(char *));
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