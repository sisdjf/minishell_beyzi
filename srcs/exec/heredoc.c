/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:07:48 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 23:00:28 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes_and_exit(t_stock *stock, int *i)
{
	while (*i < stock->nb_hd)
	{
		close(stock->heredoc[*i].fd_heredoc[1]);
		close(stock->heredoc[*i].fd_heredoc[0]);
		*i += 1;
	}
	exit(1);
}

void	exec_heredoc(t_stock *stock, int *i)
{
	signal(SIGINT, &ft_gestion_heredoc);
	while (*i < stock->nb_hd)
	{
		close(stock->heredoc[*i].fd_heredoc[0]);
		if (prompt_heredoc(stock, stock->heredoc[*i].lim,
				stock->heredoc[*i].fd_heredoc[1]) == 1)
		{
			free_heredoc(stock->heredoc, stock);
			exit(1);
		}
		(*i)++;
	}
	free_heredoc(stock->heredoc, stock);
	free_exec(stock);
	free_tokens(&stock->token);
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
		if (g_globale > 0)
			return (close(pipe), 1);
		if (!line)
		{
			ft_printf("warning: here-document at line\n",
				"%d delimited by end-of-file (wanted '%s')\n",
				lim);
			break ;
		}
		if (!ft_strcmp(line, lim))
			break ;
		ft_putendl_fd(line, pipe);
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
			heredoc[i].totalsize = stock->nb_hd;
			heredoc[i].index_cmd = i;
			heredoc[i].lim = ft_strdup(tmp->next->name);
			pipe(heredoc[i].fd_heredoc);
			i++;
			printf("[%s]\n", heredoc[i].lim);
		}
		tmp = tmp->next;
	}
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
	stock->heredoc = heredoc;
	if (!heredoc)
		return (ft_printf("!!! erreur malloc t_heredoc !!!\n"), 1);
	init_heredoc(stock, heredoc);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_heredoc(stock, &i);
	else if (pid > 0)
	{
		while (i < stock->nb_hd)
			close(heredoc[i++].fd_heredoc[1]);
	}
	signal(SIGINT, &ft_gestion);
	waitpid(pid, &i, 0);
	return (WEXITSTATUS(i));
}
