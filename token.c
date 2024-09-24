/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:34:50 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/24 13:56:34 by lybey            ###   ########.fr       */
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

// void	chr_op_space(char *str, int *i)
// {
// 	while(str[(*i)])
// 	{
		
// 		if(ft_strncmp(str + (*i), ">", 1) == 0)
			
// 		(*i)++;
// 	}
	
// }
// creer struct token, chercher les operators dedans
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

// redirection
// <
// >
// <<
// >
// >

// fichier
// a
// b
// -R
// ls
// bonjour

// arguments
// echo
// -l
// hello

// commande
// hello

// struct token
// {
//     char **files = ["ls", "-R", "bonjour", "a", "b"];
//     char **arg = ["hello", "echo", "-l"];
//     int *redir = [1, 2, 4, 2, 2];
//     char *cmd = arg[0];
// };

// apres un chevron CEST FORCEMENT un fichier
// tout ce qui est ni un fichier ni une redirection EST un argument
// le premier argument = la commande

// -R > avion < ls >> bonjour < echo -s
