/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:27:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 02:23:52 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*ft_lstnew_redir(char *str, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_redir(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	last = *redir;
	if (*redir)
	{
		while (last && last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
	else
		*redir = new;
}

int	malloc_redir(t_token *token, int i)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;

	tmp = token;
	nb_malloc = 0;
	compteur = 0;
	while (compteur < i)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			nb_malloc++;
		}
		tmp = tmp->next;
	}
	return (nb_malloc);
}

int	nbr_malloc_word_cmd(t_token *token, int i)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;

	tmp = token;
	nb_malloc = 0;
	compteur = 0;
	while (compteur < i)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp)
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

	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_word_cmd(stock->token, pipe);
	new->args = ft_calloc(sizeof(char *), nb_malloc + 1);
	tmp = index_token(stock->token, pipe);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			new->args[i++] = ft_strdup(tmp->name);
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	new->args[i] = NULL;
	new->redir = new_func_with_bilel(stock->token, pipe);
	return (0);
}
