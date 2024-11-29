/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:10 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 01:00:38 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_envp_list(t_envp **envp)
{
	t_envp	*tmp;

	while (*envp)
	{
		tmp = (*envp)->next;
		if ((*envp)->env_str)
			free((*envp)->env_str);
		if ((*envp)->key)
			free((*envp)->key);
		if ((*envp)->value)
			free((*envp)->value);
		free(*envp);
		*envp = tmp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_redir(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		if ((*redir)->filename)
		{
			free((*redir)->filename);
		}
		free(*redir);
		*redir = tmp;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->args)
			free_tab((*cmd)->args);
		if ((*cmd)->redir)
			free_redir(&(*cmd)->redir);
		free(*cmd);
		*cmd = tmp;
	}
}

void	free_exec(t_stock *stock)
{
	if (stock->exec.env)
		free_tab(stock->exec.env);
	free(stock->exec.path);
}
