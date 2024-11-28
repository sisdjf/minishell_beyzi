/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:03:13 by lybey             #+#    #+#             */
/*   Updated: 2024/11/28 03:31:10 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*ft_lstnew_cmd(t_stock *stock, int pipe)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->redir = NULL;
	stock_args_cmd(stock, pipe, new);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	last = *cmd;
	if (*cmd)
	{
		while (last && last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
	else
		*cmd = new;
}

int	nb_cmd(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type && tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i + 1);
}

int	find_real_nb_cmd(t_token *tok)
{
	t_token	*tmp;
	int		nb_malloc;

	nb_malloc = 0;
	tmp = tok;
	while (tmp)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
			tmp = tmp->next;
		else if (tmp->type == WORD)
		{
			while (tmp && tmp->type != PIPE)
				tmp = tmp->next;
			nb_malloc++;
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (nb_malloc);
}

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

void	stock_cmd_lst(t_stock *stock)
{
	t_stock	*tmp;
	t_cmd	*new_node;
	int		cmds;
	int		compteur;

	tmp = stock;
	compteur = 0;
	cmds = nb_cmd(stock->token);
	while (compteur < cmds)
	{
		new_node = ft_lstnew_cmd(tmp, compteur);
		if (new_node)
		{
			ft_lstadd_back_cmd(&stock->cmd, new_node);
		}
		compteur++;
	}
	stock->exec.nb_cmd = nb_cmd(stock->token);
	stock->nb_hd = find_nb_hdoc(stock->token);
}
