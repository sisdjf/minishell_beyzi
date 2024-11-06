/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:03:13 by lybey             #+#    #+#             */
/*   Updated: 2024/11/07 00:24:40 by lybey            ###   ########.fr       */
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
	}// int	get_nb_words(t_token *token)
// {
// 	t_token	*tmp;
// 	int		word;

// 	tmp = token;
// 	word = 0;
// 	while (tmp)
// 	{
// 		if (tmp->name)
// 		{
// 			if (tmp->type == WORD)
// 			{
// 				word++;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (word);
// }
// pas encore adapte pour les |
// void	tok_to_tab(t_stock *stock)
// {
// 	int i;
// 	int j;
// 	t_stock *tmp;

// 	i = 0;
// 	j = 0;
// 	tmp = stock;
// 	i = get_nb_words(stock->token);
// 	// printf("iiiiiiiiiiiiiiii %d\n", i);
// 	tmp->tab = malloc(sizeof(char *) * (i + 1));
// 	if (!tmp->tab)
// 	{
// 		printf("Error tab malloc\n");
// 		return ;
// 	}
// 	while (tmp->token)
// 	{
// 		if (tmp->token->name)
// 		{
// 			// printf("--------- temp->name = %s\n", tmp->token->name);
// 			if (tmp->token->type == WORD)
// 			{
// 				tmp->tab[j] = ft_strdup(tmp->token->name);
// 				if (!tmp->tab[j])
// 					printf("error tab\n");
// 				// printf("---------- stock->tab[%d] = %s\n", j, stock->tab[j]);
// 				j++;
// 			}
// 		}
// 		tmp->token = tmp->token->next;
// 	}
// 	// printf("jjjjjjj = %d\n iiiii = %d\n", j, i);
// 	tmp->tab[j] = NULL;
// }
	new->args = malloc(sizeof(char *) * (nb_malloc + 1));
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

t_cmd	*ft_lstnew_cmd(t_token *token, int pipe)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
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
		// free(new_node);
		compteur++;
	}
	stock->exec.nb_cmd = cmds;
}
