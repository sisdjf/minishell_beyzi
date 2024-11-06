/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/11/06 02:49:43 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_builtins(char **cmd)
{
	if (!cmd || !cmd[0])
		return (1);
	if (!strcmp(cmd[0], "echo"))
		return (1);
	else if (!strcmp(cmd[0], "cd"))
		return (1);
	else if (!strcmp(cmd[0], "pwd"))
		return (1);
	else if (!strcmp(cmd[0], "export"))
		return (1);
	else if (!strcmp(cmd[0], "unset"))
		return (1);
	else if (!strcmp(cmd[0], "env"))
		return (1);
	else if (!strcmp(cmd[0], "exit"))
		return (1);
	return (0);
}

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
