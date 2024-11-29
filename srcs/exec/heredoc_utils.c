/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:09:18 by lybey             #+#    #+#             */
/*   Updated: 2024/11/29 02:14:59 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_heredoc(t_heredoc *heredoc, t_stock *stock)
{
	int	i;
	int	x;

	if (stock->nb_hd == 0)
		return ;
	i = 0;
	x = heredoc->totalsize;
	while (i < x)
	{
		if (heredoc[i].lim)
			free(heredoc[i].lim);
		close(heredoc[i].fd_heredoc[0]);
		close(heredoc[i].fd_heredoc[1]);
		i++;
	}
	if (x)
		free(heredoc);
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
		free_heredoc(stock->heredoc, stock);
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
	free_exec(stock);
	free_tokens(&stock->token);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
	free_heredoc(stock->heredoc, stock);
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
