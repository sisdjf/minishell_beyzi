/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:34:50 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/28 16:26:04 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(char *str, int *i)
{
	while (str[(*i)] == ' ' || (str[(*i)] >= 9 && str[(*i)] <= 13))
	{
		(*i)++;
	}
}

void	chr_operator(char *input, t_token *token, int *i)
{
	char	*str;
	int		cmpt;
	int		index_str;
	int		j;

		if (ft_strncmp(input + (*i), ">>", 2) == 0)
		{
			token->name = ft_strdup(">>");
			token->type = D_REDIR_R;
			printf("type >>: %d\n", token->type);
			token->next = NULL;
			(*i)++;
			return ;
		}
		else if (ft_strncmp(input + (*i), "<<", 2) == 0)
		{
			token->name = ft_strdup("<<");
			token->type = HERDOC;
			printf("type <<: %d\n", token->type);
			token->next = NULL;
			(*i)++;
			return ;
		}
		else if (ft_strncmp(input + (*i), ">", 1) == 0)
		{
			token->name = ft_strdup(">");
			token->type = REDIR_R;
			printf("type >: %d\n", token->type);
			token->next = NULL;
			return ;
		}
		else if (ft_strncmp(input + (*i), "<", 1) == 0)
		{
			token->name = ft_strdup("<");
			token->type = REDIR_L;
			printf("type <: %d\n", token->type);
			token->next = NULL;
			return ;
		}
		else if (ft_strncmp(input + (*i), "|", 1) == 0)
		{
			token->name = ft_strdup("|");
			token->type = PIPE;
			printf("type |: %d\n", token->type);
			token->next = NULL;
			return ;
		}
	// }
	else
	{
		j = (*i);
		cmpt = 0;
		index_str = 0;
		while (input[j] && (input[j] != ' ' && input[j] != '|' && input[j] != '>' && input[j] != '<'))
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
		token->type = WORD;
		printf("type word: %d\n", token->type);
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
		chr_operator(input, new_token, &i);
		ft_lstadd_back(&stock->token, new_token);
		printf("token = %s\n", new_token->name);
		i++;
	}
	return (0);
}
