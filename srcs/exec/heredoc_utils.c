/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:09:18 by lybey             #+#    #+#             */
/*   Updated: 2024/11/19 23:55:00 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void    ft_heredoc(t_stock *stock, t_token *token)
// {
//     t_token *tmp;

//     tmp = token;
//     while(1)
//     {
// 		if (tmp->type == HERDOC)
//         {
            
//         }
//     }
    
    
// }

void	find_nb_hdoc(t_stock *stock, t_heredoc *heredoc)
{
	t_token	*tmp;

	heredoc->nb_hd = 0;
	tmp = stock->token;
	while (tmp)
	{
		if (tmp->type == HERDOC)
		{
			heredoc->nb_hd++;
		}
		tmp = tmp->next;
	}
}

void	init_here_doc(t_stock *stock, t_heredoc *heredoc)
{
	t_token	*tmp;
	int		i;

	tmp = stock->token;
	i = 0;
	while (i < heredoc->nb_hd)
	{
		if (tmp->type == HERDOC)
		{
			heredoc->index_cmd = i;// utile ?
			heredoc->lim = stock->cmd->heredoc[i];
			pipe(heredoc->fd_heredoc);
			i++;
		}
		tmp = tmp->next;
	}
}

void	stock_heredoc(t_stock *stock, t_heredoc *heredoc)
{
	int			i;
	int			pid;

	i = 0;
	if (heredoc->nb_hd == 0)
		return ;
	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return ;
	init_here_doc(stock, heredoc);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		exec_heredoc(stock, &i);
	else if (pid > 0)
	{
		while (i < heredoc->nb_hd)
			close(heredoc[i++].fd_heredoc[1]);
	}
	signal(SIGINT, &ft_gestion);
	waitpid(pid, 0, 0);
}

void	exec_heredoc(t_stock *stock, int *i)
{
	signal(SIGINT, &ft_gestion);
	while (*i < stock->heredoc->nb_hd)
	{
		close(stock->heredoc[*i].fd_heredoc[0]);
		// write_hdocs(stock->heredoc[*i].lim, stock->heredoc[*i].fd_heredoc[1], stock);
		(*i)++;
	}
	if (stock->flag_hd == 1)
	{
		dup2(stock->heredoc->fd_heredoc[0], STDIN_FILENO);
		dup2(stock->heredoc->fd_heredoc[1], STDOUT_FILENO);
		close(stock->heredoc->fd_heredoc[0]);
		close(stock->heredoc->fd_heredoc[1]);
		// free_tab(stock->builtin);
	}
	free(stock->heredoc);
	// free_export(stock->env_export);
	// free_tok(tok);
	exit(0);
}