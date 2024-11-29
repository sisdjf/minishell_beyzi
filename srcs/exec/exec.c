/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 03:03:55 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_exec(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->exec.nb_cmd)
	{
		if (pipe(stock->exec.fd_pipe) == -1)
			return (printf("Error avec la fonction pipe\n"), EXIT_FAILURE);
		stock->exec.pid[i] = fork();
		if (stock->exec.pid[i] < 0)
			return (printf("ERROR FORK\n"), EXIT_FAILURE);
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
	finish_exec(stock, i);
	return (stock->exit_status);
}

void	finish_exec(t_stock *stock, int i)
{
	if (stock->exec.nb_cmd)
	{
		close(stock->exec.fd_pipe[1]);
		close(stock->exec.fd_pipe[0]);
	}
	i = 0;
	analys_finish_process(stock, &i);
	close_heredoc_child(stock);
}

void	analys_finish_process(t_stock *stock, int *i)
{
	while ((*i) < stock->exec.nb_cmd)
	{
		waitpid(stock->exec.pid[*i++], &stock->exit_status, 0);
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
