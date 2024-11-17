/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/11/18 00:43:48 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

int	builtins(t_stock *stock, char **cmd, t_envp **envp)
{
	if (!cmd || !cmd[0])
		return (stock->exit_status = 1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (stock->exit_status = echo(stock, cmd), 1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (stock->exit_status = ft_cd(cmd, *envp), 1);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (stock->exit_status = pwd(cmd), 1);
	else if (!ft_strcmp(cmd[0], "export"))
		return (stock->exit_status = export(cmd, envp), 1);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (stock->exit_status = ft_unset(cmd, *envp), 1);
	else if (!ft_strcmp(cmd[0], "env"))
		return (env(*envp), 1);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (stock->exit_status = ft_exit(stock, cmd), 1);
	return (stock->exit_status = 0);
}

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
	res = ft_calloc((i + 1), sizeof(char *));
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
