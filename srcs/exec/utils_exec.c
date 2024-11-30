/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:17:43 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 16:08:32 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_child(t_stock *stock)
{
	free_exec(stock);
	free_tokens(&stock->token);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
}

void	analys_finish_process(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->exec.nb_cmd)
	{
		waitpid(stock->exec.pid[i++], &stock->exit_status, 0);
		if (WIFEXITED(stock->exit_status))
			stock->exit_status = WEXITSTATUS(stock->exit_status);
		else if (WIFSIGNALED(stock->exit_status))
		{
			stock->exit_status = 128 + WTERMSIG(stock->exit_status);
			stock->signal = stock->exit_status;
		}
		else if (WIFSTOPPED(stock->exit_status))
			stock->exit_status = 128 + WSTOPSIG(stock->exit_status);
	}
}

char	*path_from_cmd(t_exec *exec)
{
	if (ft_strchr(exec->cmd, '/'))
	{
		if (access(exec->cmd, F_OK | X_OK) == 0)
			return(ft_strdup(exec->cmd));
	}
	// ft_printf("bash: %s: Command not found\n", exec->cmd);
	return (NULL);
}

char	*path_to_cmd(t_stock *stock, t_exec *exec, t_envp *envp)
{
	int		i;
	char	*cmd_path;
	char	*tmp;

	cmd_path = path_from_cmd(exec);
	if(cmd_path)
		return(cmd_path);
	exec->path = chr_path(stock, envp);
	i = -1;
	if (!exec->path)
		return (stock->exit_status = 127, NULL);
	exec->split_path = ft_split(exec->path, ':');
	i = 0;
	while (exec->split_path[i])
	{
		tmp = ft_strjoin(exec->split_path[i], "/");
		cmd_path = ft_strjoin(tmp, exec->cmd);
		if (!cmd_path)
			return (free(exec->split_path), free(cmd_path), free(tmp), (NULL));
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (free_split(exec->split_path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (free_split(exec->split_path), NULL);
}

char	**tab_env(t_exec *exec, t_envp *envp)
{
	char	**env;
	t_envp	*tmp;

	int (i) = 0;
	int (size) = 0;
	(void)exec;
	tmp = envp;
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
