/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:34:50 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/06 21:45:35 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_space(char *str, int *i)
{
	while (str[(*i)] == ' ' || (str[(*i)] >= 9 && str[(*i)] <= 13))
	{
		(*i)++;
	}
}

void	stock_word(t_token *token, char *input, int *i)
{
	char	*str;
	int		cmpt;
	int		index_str;
	int		j;

	j = (*i);
	cmpt = 0;
	index_str = 0;
	while (input[j] && (input[j] != ' ' && input[j] != '|' && input[j] != '>'
			&& input[j] != '<'))
	{
		j++;
		cmpt++;
	}
	str = malloc(sizeof(char) * (cmpt + 1));
	while (index_str < cmpt)
	{
		str[index_str] = input[(*i)];
		(*i)++;
		index_str++;
	}
	str[index_str] = '\0';
	token->name = str;
}

void	chr_operator(char *input, t_token *token, int *i, int j)
{
	if (ft_strncmp(input + (*i), ">>", 2) == 0)
		stock_redir_double_r(token, i);
	else if (ft_strncmp(input + (*i), "<<", 2) == 0)
		stock_heredoc(token, i);
	else if (ft_strncmp(input + (*i), ">", 1) == 0)
		stock_redir_r(token);
	else if (ft_strncmp(input + (*i), "<", 1) == 0)
		stock_redir_l(token);
	else if (ft_strncmp(input + (*i), "|", 1) == 0)
		stock_pipe(token);
	else
	{
		j = (*i);
		stock_word(token, input, i);
		token->type = WORD;
		token->next = NULL;
		(*i)--;
		return ;
	}
}

int	ft_token(t_stock *stock, char *input)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (input[i])
	{
		skip_space(input, &i);
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (printf("error malloc token"), 1);
		chr_operator(input, new_token, &i, 0);
		fprintf(stderr,"my token is %s\n", new_token->name);
		new_token->name = ft_positif(new_token->name);
		ft_lstadd_back(&stock->token, new_token);
		i++;
	}
	return (0);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		if (token->name)
			free(token->name);
		free(token);
		token = tmp;
	}
}
