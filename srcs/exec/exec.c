/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/27 02:18:11 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_struct_exec(t_stock *stock, int i)
{
	stock->exec.cmd = ft_find_cmd_for_exec(stock, i);
	if (!stock->exec.cmd)
		return (1);
	stock->exec.cmd_tab = ft_find_tab(stock, i);
	stock->exec.path = path_to_cmd(stock, &stock->exec, stock->envp);
	stock->exec.env = tab_env(&stock->exec, stock->envp);
	return (0);
}
char	*chr_path(t_stock *stock, t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	stock->exit_status = 127;
	return (NULL);
}

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
	// if (!exec->path)
	// {
	// 	free(exec->path);
	// 	return (free(exec->path), NULL);
	// }
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

void	print_vraitab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
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

char	**ft_find_tab(t_stock *stock, int i)
{
	int		compteur;
	t_cmd	*tmp;

	compteur = 0;
	tmp = stock->cmd;
	while (tmp)
	{
		if (compteur == i)
		{
			if (tmp->args[1])
				return (tmp->args);
		}
		compteur++;
		tmp = tmp->next;
	}
	return (NULL);
}

void	pipe_redir(t_stock *stock, int i)
{
	if (i != 0)
	{
		dup2(stock->exec.fd_tmp, 0);
		close(stock->exec.fd_tmp);
	}
	if (i != stock->exec.nb_cmd - 1)
		dup2(stock->exec.fd_pipe[1], 1);
	close(stock->exec.fd_pipe[0]);
	close(stock->exec.fd_pipe[1]);
	// close_fds(stock);
}

char	*ft_find_cmd_for_exec(t_stock *stock, int i)
{
	t_cmd	*tmp;
	int		compteur;

	compteur = 0;
	tmp = stock->cmd;
	while (tmp)
	{
		if (compteur == i)
		{
			return (tmp->args[0]);
		}
		compteur++;
		tmp = tmp->next;
	}
	return (NULL);
}
int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_child(t_stock *stock, int i)
{
	// default_signals();
	if (init_struct_exec(stock, i))
	{
		fprintf(stderr, "je suis \n");
		do_redir(stock->cmd, i, stock->heredoc);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		free_heredoc(stock->heredoc);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
	}
	pipe_redir(stock, i);
	// do_redir(stock->cmd, i, stock->heredoc);
	if (do_redir(stock->cmd, i, stock->heredoc) == 1)
	{
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		free_heredoc(stock->heredoc);
		exit(EXIT_FAILURE);
	}
	if (check_builtins(stock->exec.cmd_tab))
	{
		builtins(stock, stock->exec.cmd_tab, &stock->envp);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		stock->exit_status = 127;
		exit(127);
	}
	if (stock->exec.path)
	{
		close(stock->exec.fd_pipe[0]);
		if (i > 0)
			close(stock->exec.fd_tmp);
		// close(stock->exec.fd_pipe[1]);
		execve(stock->exec.path, stock->exec.cmd_tab, stock->exec.env);
		if (is_directory(stock->exec.cmd))
			printf("bash: %s: Is a directory\n", stock->exec.cmd);
		else
			ft_printf("bash: %s: : No such file or directory\n",
						stock->exec.cmd);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		stock->exit_status = 127;
		exit(127);
	}
	else
	{
		if (stock->exec.cmd)
		{
			if (ft_strcmp(stock->exec.cmd, "$?") == 0)
				ft_printf("bash: %d: command not found\n", stock->exit_status);
			else
				ft_printf("bash: %s: command not found\n", stock->exec.cmd);
			stock->exit_status = 127;
			free_exec(stock);
			free_tokens(&stock->token);
			ft_free_envp_list(&stock->envp);
			free_cmd(&stock->cmd);
			// if (stock->heredoc)
			// {
			// 	close_heredoc_child(stock);
			// }
			close(stock->exec.fd_pipe[0]);
			close(stock->exec.fd_pipe[1]);
			exit(127);
		}
		stock->exit_status = 0;
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		free_heredoc(stock->heredoc);
		// if (stock->heredoc)
		// {
		// 	close_heredoc_child(stock);
		// }
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
		// exit ici si ya erreur avec un beau jolie msg derreur puis free
	}
	return (0);
}

int	ft_exec(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->exec.nb_cmd)
	{
		if (pipe(stock->exec.fd_pipe) == -1)
		{
			printf("Error avec la fonction pipe\n");
			return (EXIT_FAILURE);
		}
		stock->exec.pid[i] = fork();
		if (stock->exec.pid[i] < 0)
		{
			printf("ERROR FORK\n");
			return (EXIT_FAILURE);
		}
		// stock->exec.fd_tmp = stock->exec.fd_pipe[0];
		if (stock->exec.pid[i] == 0)
		{
			default_signals();
			stock->exit_status = ft_child(stock, i);
			return (127);
		}
		close(stock->exec.fd_pipe[1]);
		if (i > 0)
			close(stock->exec.fd_tmp);
		stock->exec.fd_tmp = stock->exec.fd_pipe[0];
		i++;
	}
	if (stock->exec.nb_cmd)
	{
		close(stock->exec.fd_pipe[1]);
		close(stock->exec.fd_pipe[0]);
	}
	i = 0;
	while (i < stock->exec.nb_cmd)
	{
		// fprintf(stderr, "PID [%i]\n", stock->exec.pid[i]);
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
	close_heredoc_child(stock);
	return (stock->exit_status);
}
