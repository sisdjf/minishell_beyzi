/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:49:26 by lybey             #+#    #+#             */
/*   Updated: 2024/11/12 17:49:50 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nbr_malloc_appendfile_cmd(t_token *token, int pipe)
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
		if (tmp->type == D_REDIR_R)
		{
			tmp = tmp->next;
			nb_malloc++;
		}
		tmp = tmp->next;
	}
	return (nb_malloc);
}

int	stock_appendfile_cmd(t_token *token, int pipe, t_cmd *new)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;
	int		i;

	tmp = token;
	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_appendfile_cmd(token, pipe);
	if (nb_malloc == 0)
	{
		new->appendfile = NULL;
		return (0);
	}
	new->appendfile = malloc(sizeof(char *) * (nb_malloc + 1));
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_REDIR_R)
		{
			tmp = tmp->next;
			new->appendfile[i++] = ft_strdup(tmp->name);
		}
		tmp = tmp->next;
	}
	new->appendfile[i] = NULL;
	return (0);
}

int	nbr_malloc_herdoc_cmd(t_token *token, int pipe)
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
		if (tmp->type == HERDOC)
		{
			tmp = tmp->next;
			nb_malloc++;
		}
		tmp = tmp->next;
	}
	return (nb_malloc);
}

int	stock_heredoc_cmd(t_token *token, int pipe, t_cmd *new)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;
	int		i;

	tmp = token;
	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_herdoc_cmd(token, pipe);
	if (nb_malloc == 0)
	{
		new->heredoc = NULL;
		return (0);
	}
	new->heredoc = malloc(sizeof(char *) * (nb_malloc + 1));
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == HERDOC)
		{
			tmp = tmp->next;
			new->heredoc[i++] = ft_strdup(tmp->name);
		}
		tmp = tmp->next;
	}
	new->heredoc[i] = NULL;
	return (0);
}
