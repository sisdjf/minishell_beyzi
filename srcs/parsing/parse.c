/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:03:13 by lybey             #+#    #+#             */
/*   Updated: 2024/11/13 22:01:05 by lybey            ###   ########.fr       */
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
	printf("nb_malloc dans nbr mallo : %d\n", nb_malloc);
	return (nb_malloc);
}

int	stock_args_cmd(t_token *token, int pipe, t_cmd *new)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;
	int		i;

	tmp = token;
	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_word_cmd(token, pipe);
	if (nb_malloc == 0)
	{
		new->infile = NULL;
		return (0);
	}
	new->args = ft_calloc(nb_malloc + 1, sizeof(char *));
	// printf("arg name : %s\n", tmp->name);
	// printf("arg type : %u\n", tmp->type);
	// printf("size nb malloc = %d\n", nb_malloc);
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		printf("tmp === %s\n", tmp->name);
		if (tmp->type == WORD)
			new->args[i++] = ft_strdup(tmp->name); // "out" 
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	new->args[i] = NULL;
	return (0);
}

t_cmd	*ft_lstnew_cmd(t_token *token, int pipe)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	stock_args_cmd(token, pipe, new);
	stock_infile_cmd(token, pipe, new);
	stock_outfile_cmd(token, pipe, new);
	stock_appendfile_cmd(token, pipe, new);
	stock_heredoc_cmd(token, pipe, new);
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

void	print_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("args ici = %s\n", cmd->args[i]);
			i++;
		}
		// i = 0;
		// while(cmd->infile[i])
		// {
		// 	printf("infile ici = %s\n", cmd->infile[i]);
		// 	i++;
		// }
		// i = 0;
		// while(cmd->outfile[i])
		// {
		// 	printf("outfile ici = %s\n", cmd->outfile[i]);
		// 	i++;
		// }
		// i = 0;
		// while(cmd->appendfile[i])
		// {
		// 	printf("appendfile ici = %s\n", cmd->appendfile[i]);
		// 	i++;
		// }
		// i = 0;
		// while(cmd->heredoc[i])
		// {
		// 	printf("heredoc ici = %s\n", cmd->heredoc[i]);
		// 	i++;
		// }
		cmd = cmd->next;
	}
}

void	stock_cmd_lst(t_stock *stock)
{
	t_token	*tmp;
	t_cmd	*new_node;
	int		cmds;
	int		compteur;

	tmp = stock->token;
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
	stock->exec.nb_cmd = cmds;

}
