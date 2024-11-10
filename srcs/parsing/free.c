/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:10 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/10 19:09:13 by sizitout         ###   ########.fr       */
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
	if (!*tab)
	{
		return ;
	}
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	int compteur = 0;
	while (*cmd)
	{
		// khalid cook stp
		// if (i == compteur)
			// tmp = tmp->next;
		tmp = (*cmd)->next;
		if ((*cmd)->args)
			free_tab((*cmd)->args);
		if ((*cmd)->infile)
			free_tab((*cmd)->infile);
		if ((*cmd)->outfile)
			free_tab((*cmd)->outfile);
		if ((*cmd)->appendfile)
			free_tab((*cmd)->appendfile);
		if ((*cmd)->heredoc)
			free_tab((*cmd)->heredoc);
		free(*cmd);
		*cmd = tmp;
		compteur++;
	}
}


//COMMENTAIRE OUR LYNDA
