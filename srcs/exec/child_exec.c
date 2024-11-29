/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 03:02:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 03:03:29 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_child(t_stock *stock, int i)
{
	default_signals();
	if (init_struct_exec(stock, i))
	{
		do_redir(stock->cmd, i, stock->heredoc);
		free_all(stock);
		free_heredoc(stock->heredoc, stock);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
	}
	pipe_redir(stock, i);
	if (do_redir(stock->cmd, i, stock->heredoc) == 1)
	{
		free_all(stock);
		free_heredoc(stock->heredoc, stock);
		exit(EXIT_FAILURE);
	}
	if (check_builtins(stock->exec.cmd_tab))
	{
		builtins(stock, stock->exec.cmd_tab, &stock->envp);
		free_all(stock);
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
		execve(stock->exec.path, stock->exec.cmd_tab, stock->exec.env);
		if (is_directory(stock->exec.cmd))
		{
			printf("bash: %s: Is a directory\n", stock->exec.cmd);
			stock->exit_status = 126;
		}
		else
		{
			ft_printf("bash: %s: : No such file or directory\n",
						stock->exec.cmd);
			stock->exit_status = 127;
		}
		free_all(stock);
		exit(stock->exit_status);
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
			free_all(stock);
			close(stock->exec.fd_pipe[0]);
			close(stock->exec.fd_pipe[1]);
			exit(127);
		}
		stock->exit_status = 0;
		free_all(stock);
		free_heredoc(stock->heredoc, stock);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
	}
	return (0);
}