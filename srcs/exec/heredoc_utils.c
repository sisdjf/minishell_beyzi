/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:09:18 by lybey             #+#    #+#             */
/*   Updated: 2024/11/26 03:13:41 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	close_pipes_and_exit(t_stock *stock, int *i)
// {
// 	// *i += 1;
// 	while (*i < stock->nb_hd)
// 	{
// 		close(stock->heredoc[*i].fd_heredoc[1]);
// 		close(stock->heredoc[*i].fd_heredoc[0]);
// 		*i += 1;
// 	}
// 	exit(1);
// }

void	exec_heredoc(t_stock *stock, int *i)
{
	// signal(SIGINT, &ft_gestion_heredoc);
	// while (*i < stock->nb_hd)
	// {
	// 	close(stock->heredoc[*i].fd_heredoc[0]);
	// 	if (prompt_heredoc(stock, stock->heredoc[*i].lim,
	// 			stock->heredoc[*i].fd_heredoc[1]) == 1)		// == 1 if signal received
	// 			close_pipes_and_exit(stock, i);
	// 	(*i)++;
	// }
	while (*i < stock->nb_hd)
	{
		close(stock->heredoc[*i].fd_heredoc[0]);
		prompt_heredoc(stock, stock->heredoc[*i].lim,
				stock->heredoc[*i].fd_heredoc[1]);
		(*i)++;
	}
	if (stock->heredoc->flag_heredoc == 1)
	{
		close(stock->heredoc->fd_heredoc[1]);
		dup2(stock->heredoc->fd_heredoc[0], STDIN_FILENO);
		// dup2(stock->heredoc->fd_heredoc[1], STDOUT_FILENO);
		close(stock->heredoc->fd_heredoc[0]);
		// free_tab(&stock->heredoc->lim);
	}
	free_tokens(&stock->token);
	free(stock->heredoc);
	free_exec(stock);
	// free_tokens(&stock->token);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
	exit(0);
}

int	prompt_heredoc(t_stock *stock, char *lim, int pipe)
{
	char	*line;
	int		i;

	i = 1;
	(void)stock;
	while (1)
	{
		line = readline("> ");
		if (g_globale > 0)	// if signal received
		{
			close(pipe);
			return (1);
		}
		if (!line)
		{
			ft_printf("warning: here-document at line\n",
						"%d delimited by end-of-file (wanted '%s')\n",
						/*stock->minishell_line_no*/ lim);
			break ;
		}
		if (!ft_strcmp(line, lim))
			break ;
		ft_putstr_fd(line, pipe);
		free(line);
		i++;
	}
	close(pipe);
	return (0);
}

void	init_heredoc(t_stock *stock, t_heredoc *heredoc)
{
	t_token	*tmp;
	int		i;

	tmp = stock->token;
	i = 0;
	if (heredoc->flag_heredoc == 1)
		heredoc->flag_heredoc = 0;
	else
		heredoc->flag_heredoc = 1;
	while (tmp && i < stock->nb_hd)
	{
		if (tmp->type == HERDOC)
		{
			heredoc[i].index_cmd = i;
			heredoc[i].lim = tmp->next->name;
			pipe(heredoc[i].fd_heredoc);
			i++;
		}
		tmp = tmp->next;
	}
}

void	close_heredoc_child(t_stock *stock)
{
	int	i;

	i = 0;
	while (i < stock->nb_hd)
	{
		close(stock->heredoc[i].fd_heredoc[0]);
		i++;
	}
	if (stock->nb_hd)
		free(stock->heredoc);
}

int	ft_heredoc(t_stock *stock)
{
	int			i;
	int			pid;
	t_heredoc	*heredoc;

	i = 0;
	if (stock->nb_hd == 0)
		return (0);
	heredoc = ft_calloc(stock->nb_hd + 1, sizeof(t_heredoc));
	if (!heredoc)
	{
		ft_printf("!!! erreur malloc t_heredoc !!!\n");
		return (1);
	}
	stock->heredoc = heredoc;
	init_heredoc(stock, heredoc);
	// signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		exec_heredoc(stock, &i);
	}
	else if (pid > 0)
	{
		while (i < stock->nb_hd)
			close(heredoc[i++].fd_heredoc[1]);
	}
	// signal(SIGINT, &ft_gestion);
	waitpid(pid, &i, 0);
	return (WEXITSTATUS(i));
}




void	ft_gestion_heredoc(int signum)
{
	t_stock	*stock;
	int		i;

	i = -1;
	(void)signum;
	stock = starton();
	write(1, "\n", 1);
	while (++i < stock->nb_hd)
	{
		close(stock->heredoc[i].fd_heredoc[1]);
		close(stock->heredoc[i].fd_heredoc[0]);
	}
	if (stock->heredoc->flag_heredoc == 1)
	{
		dup2(stock->fd_std[0], STDIN_FILENO);
		dup2(stock->fd_std[1], STDOUT_FILENO);
		close(stock->fd_std[0]);
		close(stock->fd_std[1]);
	}
	free_exec(stock);
	free_tokens(&stock->token);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
	exit(130);
}
void	disable_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}