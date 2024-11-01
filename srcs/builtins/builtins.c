/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/10/31 23:07:49 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtins(char **cmd, t_envp *envp)
{
	if (!cmd || !cmd[0])
		return (1);
	if (!strcmp(cmd[0], "echo"))
		return (echo(cmd), 1);
	else if (!strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, envp), 1);
	else if (!strcmp(cmd[0], "pwd"))
		return (pwd(cmd), 1);
	else if (!strcmp(cmd[0], "export"))
		return (export(cmd, envp), 1);
	else if (!strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, envp), 1);
	else if (!strcmp(cmd[0], "env"))
		return (env(envp), 1);
	else if (!strcmp(cmd[0], "exit"))
		return (ft_exit(cmd), 1);
	return (0);
}

// int	get_nb_words(t_token *token)
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

int	get_nb_words(t_token *token)
{
	t_token	*tmp;
	int		word;

	word = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->name && tmp->type == WORD)
		{
			word++;
		}
		tmp = tmp->next;
	}
	return (word);
}
// pourquoi on segfault quand on verifie si stock->token (token) est vide? (c'est pas vide)
char	**tok_to_tab(t_token *token)
{
	int		i;
	int		j;
	t_token	*token_tmp;
	char	**res;

	if (!token)
	{
		printf("Error: NULL token\n");
		return (NULL);
	}
	token_tmp = token;
	i = get_nb_words(token_tmp);
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
	{
		printf("Error: tab malloc failed\n");
		return (NULL);
	}
	j = 0;
	while (token_tmp)
	{
		if (token_tmp->name && token_tmp->type == WORD)
		{
			res[j] = ft_strdup(token_tmp->name);
			if (!res[j])
				return (NULL);
			j++;
		}
		token_tmp = token_tmp->next;
	}
	res[j] = NULL;
	return (res);
}
