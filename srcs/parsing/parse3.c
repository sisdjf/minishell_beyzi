/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:46:33 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:10:23 by sizitout         ###   ########.fr       */
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

int	new_func_with_bilel(t_token *tok, int i, t_cmd *new)
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
			if (new_node == NULL)
				return (1);
			ft_lstadd_back_redir(&head, new_node);
		}
		tmp = tmp->next;
	}
	new->redir = head;
	return (0);
}
