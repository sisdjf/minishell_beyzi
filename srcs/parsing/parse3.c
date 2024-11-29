/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:46:33 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 02:05:56 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*index_token(t_token *token, int pipe)
{
	int		compteur;
	t_token	*tmp;

	tmp = token;
	compteur = 0;
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	return (tmp);
}

t_redir	*new_func_with_bilel(t_token *tok, int i)
{
	int		compteur;
	t_redir	*head;
	t_token	*tmp;
	t_redir	*new_node;

	compteur = 0;
	head = NULL;
	tmp = index_token(tok, i);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			new_node = ft_lstnew_redir(tmp->next->name, tmp->type);
			if (new_node)
				ft_lstadd_back_redir(&head, new_node);
		}
		tmp = tmp->next;
	}
	return (head);
}

int	bon_heredoc(t_heredoc *here, char *file)
{
	int	i;

	i = 0;
	while (i < here->totalsize)
	{
		if (ft_strcmp(file, here[i].lim) == 0)
			return (here[i].fd_heredoc[0]);
		i++;
	}
	return (-1);
}

int	fd_filename(t_cmd *cmd, t_heredoc *here)
{
	int		fd;
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_R)
			fd = open(tmp->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->type == D_REDIR_R)
			fd = open(tmp->filename, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (tmp->type == REDIR_L)
			fd = open(tmp->filename, O_RDONLY);
		else if (tmp->type == HERDOC)
			fd = bon_heredoc(here, tmp->filename);
		if (fd == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (fd);
}
