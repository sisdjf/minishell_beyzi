/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:28:56 by lybey             #+#    #+#             */
/*   Updated: 2024/11/26 18:58:48 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	nbr_malloc_infile_cmd(t_token *token, int pipe)
// {
// 	t_token	*tmp;
// 	int		nb_malloc;
// 	int		compteur;

// 	nb_malloc = 0;
// 	tmp = token;
// 	compteur = 0;
// 	while (compteur < pipe)
// 	{
// 		if (tmp->type == PIPE)
// 			compteur++;
// 		tmp = tmp->next;
// 	}
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == REDIR_L)
// 		{
// 			tmp = tmp->next;
// 			nb_malloc++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (nb_malloc);
// }

// int	stock_infile_cmd(t_token *token, int pipe, t_cmd *new)
// {
// 	t_token	*tmp;
// 	int		nb_malloc;
// 	int		compteur;
// 	int		i;

// 	tmp = token;
// 	compteur = 0;
// 	i = 0;
// 	nb_malloc = nbr_malloc_infile_cmd(token, pipe);
// 	if (nb_malloc == 0)
// 	{
// 		new->infile = NULL;
// 		return (0);
// 	}
// 	new->infile = malloc(sizeof(char *) * (nb_malloc + 1));
// 	while (compteur < pipe)
// 	{
// 		if (tmp->type == PIPE)
// 			compteur++;
// 		tmp = tmp->next;
// 	}
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == REDIR_L)
// 		{
// 			tmp = tmp->next;
// 			new->infile[i++] = ft_strdup(tmp->name);
// 		}
// 		tmp = tmp->next;
// 	}
// 	new->infile[i] = NULL;
// 	return (0);
// }

// int	nbr_malloc_outfile_cmd(t_token *token, int pipe)
// {
// 	t_token	*tmp;
// 	int		nb_malloc;
// 	int		compteur;

// 	nb_malloc = 0;
// 	tmp = token;
// 	compteur = 0;
// 	while (compteur < pipe)
// 	{
// 		if (tmp->type == PIPE)
// 			compteur++;
// 		tmp = tmp->next;
// 	}
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == REDIR_R)
// 		{
// 			tmp = tmp->next;
// 			nb_malloc++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (nb_malloc);
// }

// int	stock_outfile_cmd(t_token *token, int pipe, t_cmd *new)
// {
// 	t_token	*tmp;
// 	int		nb_malloc;
// 	int		compteur;
// 	int		i;

// 	tmp = token;
// 	compteur = 0;
// 	i = 0;
// 	nb_malloc = nbr_malloc_outfile_cmd(token, pipe);
// 	if (nb_malloc == 0)
// 	{
// 		new->outfile = NULL;
// 		return (0);
// 	}
// 	new->outfile = malloc(sizeof(char *) * (nb_malloc + 1));
// 	while (compteur < pipe)
// 	{
// 		if (tmp->type == PIPE)
// 			compteur++;
// 		tmp = tmp->next;
// 	}
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == REDIR_R)
// 		{
// 			tmp = tmp->next;
// 			new->outfile[i] = ft_strdup(tmp->name);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	new->outfile[i] = NULL;
// 	return (0);
// }
