/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:36:01 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/01 16:35:24 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	stock_redir_double_r(t_token *token, int *i)
{
	token->name = ft_strdup(">>");
	token->type = D_REDIR_R;
	token->next = NULL;
	(*i)++;
	return ;
}

void	stock_heredoc(t_token *token, int *i)
{
	token->name = ft_strdup("<<");
	token->type = HERDOC;
	token->next = NULL;
	(*i)++;
	return ;
}

void	stock_redir_r(t_token *token)
{
	token->name = ft_strdup(">");
	token->type = REDIR_R;
	token->next = NULL;
	return ;
}

void	stock_pipe(t_token *token)
{
	token->name = ft_strdup("|");
	token->type = PIPE;
	token->next = NULL;
	return ;
}

void	stock_redir_l(t_token *token)
{
	token->name = ft_strdup("<");
	token->type = REDIR_L;
	token->next = NULL;
	return ;
}
