/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:03:13 by lybey             #+#    #+#             */
/*   Updated: 2024/11/24 01:09:56 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// creer la structure //
// remplir le tableau de chaque maillon avec les cmd args avant le pipe
//         trouver le pipe, avancer sur le maillon

int	nbr_malloc_word_cmd(t_token *token, int pipe)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;

	nb_malloc = 0;
	tmp = token;
	compteur = 0;
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			nb_malloc++;
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (nb_malloc);
}

int	stock_args_cmd(t_stock *stock, int pipe, t_cmd *new)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;
	int		i;

	tmp = stock->token;
	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_word_cmd(stock->token, pipe);
	// if (nb_malloc == 0)
	// {
	// 	new->infile = NULL;
	// 	return (0);
	// }
	new->args = ft_calloc(sizeof(char *), nb_malloc + 1);
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			new->args[i++] = ft_strdup(tmp->name);
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	new->args[i] = NULL;
	return (0);
}

t_cmd	*ft_lstnew_cmd(t_stock *stock, int pipe)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	stock_args_cmd(stock, pipe, new);
	stock_infile_cmd(stock->token, pipe, new);
	stock_outfile_cmd(stock->token, pipe, new);
	stock_appendfile_cmd(stock->token, pipe, new);
	stock_heredoc_cmd(stock, pipe, new);
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

int find_real_nb_cmd(t_token *tok)
{
	t_token *tmp;
	int nb_malloc;

	nb_malloc = 0;
	tmp = tok;
	while(tmp)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
			tmp = tmp->next;
		else if (tmp->type == WORD)
		{
			while(tmp && tmp->type != PIPE)
				tmp = tmp->next;
			nb_malloc++;
		}
		if(tmp)
			tmp = tmp->next;
	}
	return (nb_malloc);
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
	stock->exec.nb_cmd = find_real_nb_cmd(stock->token);

}
