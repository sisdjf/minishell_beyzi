/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:55:56 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:10:52 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_nb_hdoc(t_token *tok)
{
	t_token	*tmp;
	int		nb_hdoc;

	tmp = tok;
	nb_hdoc = 0;
	while (tmp)
	{
		if (tmp->type == HERDOC)
			nb_hdoc++;
		tmp = tmp->next;
	}
	return (nb_hdoc);
}

int	bon_heredoc1(t_redir *tmp)
{
	int	fd[2];
	int	i;

	i = 0;
	if (pipe(fd) == -1)
		return (-1);
	while (tmp->heredoc_content && tmp->heredoc_content[i])
	{
		ft_putendl_fd(tmp->heredoc_content[i], fd[1]);
		i++;
	}
	close(fd[1]);
	return (fd[0]);
}

int	fd_redir(t_redir *tmp)
{
	int	fd;

	if (tmp->type == REDIR_R)
		fd = open(tmp->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
	else if (tmp->type == D_REDIR_R)
		fd = open(tmp->filename, O_CREAT | O_RDWR | O_APPEND, 0666);
	else if (tmp->type == REDIR_L)
		fd = open(tmp->filename, O_RDONLY);
	else if (tmp->type == HERDOC)
		fd = bon_heredoc1(tmp);
	else
		return (-1);
	if (fd == -1)
		return (-1);
	if (tmp->type == REDIR_R || tmp->type == D_REDIR_R)
		dup2(fd, STDOUT_FILENO);
	else if (tmp->type == HERDOC || tmp->type == REDIR_L)
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	do_redir(t_cmd *cmd, int i)
{
	t_redir	*tmp;
	t_cmd	*tmp_cmd;
	int		go_to;

	go_to = 0;
	tmp_cmd = cmd;
	while (go_to < i)
	{
		tmp_cmd = tmp_cmd->next;
		go_to++;
	}
	tmp = tmp_cmd->redir;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (fd_redir(tmp) == -1)
		{
			ft_error(-1, tmp->filename);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
