/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 19:56:16 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 00:03:42 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_child(t_stock *stock, int i)
{
	if (init_struct_exec(stock, i))
	{
		do_redir(stock->cmd, i, stock->heredoc);
		free_init_child(stock);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
	}
	pipe_redir(stock, i);
	if (do_redir(stock->cmd, i, stock->heredoc) == 1)
	{
		free_child(stock);
		free_heredoc(stock->heredoc, stock);
		exit(EXIT_FAILURE);
	}
	if (check_builtins(stock->exec.cmd_tab))
	{
		builtins(stock, stock->exec.cmd_tab, &stock->envp);
		free_child(stock);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		stock->exit_status = 127;
		exit(127);
	}
}

void	exec_child(t_stock *stock, const int i)
{
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
		free_child(stock);
		exit(stock->exit_status);
	}
}

void	ft_child(t_stock *stock, int i)
{
	default_signals();
	init_child(stock, i);
	if (stock->exec.path)
		exec_child(stock, i);
	else
	{
		if (stock->exec.cmd)
		{
			if (ft_strcmp(stock->exec.cmd, "$?") == 0)
				ft_printf("bash: %d: command not found\n", stock->exit_status);
			else
				ft_printf("bash: %s: command not found\n", stock->exec.cmd);
			stock->exit_status = 127;
			// free_child(stock);
			free_cmd(&stock->cmd);
			close(stock->exec.fd_pipe[0]);
			close(stock->exec.fd_pipe[1]);
			exit(127);
		}
		stock->exit_status = 0;
		free_child(stock);
		free_heredoc(stock->heredoc, stock);
		close(stock->exec.fd_pipe[0]);
		close(stock->exec.fd_pipe[1]);
		exit(0);
	}
}

int	handle_child(t_stock *stock, int *i)
{
	if (pipe(stock->exec.fd_pipe) == -1)
	{
		printf("Error avec la fonction pipe\n");
		return (EXIT_FAILURE);
	}
	stock->exec.pid[*i] = fork();
	if (stock->exec.pid[*i] < 0)
	{
		printf("ERROR FORK\n");
		return (EXIT_FAILURE);
	}
	if (stock->exec.pid[*i] == 0)
	{
		default_signals();
		ft_child(stock, *i);
		return (127);
	}
	close(stock->exec.fd_pipe[1]);
	if (*i > 0)
		close(stock->exec.fd_tmp);
	stock->exec.fd_tmp = stock->exec.fd_pipe[0];
	return (EXIT_SUCCESS);
}

int	ft_exec(t_stock *stock)
{
	int	ret_value;
	int	i;

	i = 0;
	while (i < stock->exec.nb_cmd)
	{
		ret_value = handle_child(stock, &i);
		if (ret_value)
			return (ret_value);
		i++;
	}
	if (stock->exec.nb_cmd)
	{
		close(stock->exec.fd_pipe[1]);
		close(stock->exec.fd_pipe[0]);
	}
	analys_finish_process(stock);
	close_heredoc_child(stock);
	return (stock->exit_status);
}
