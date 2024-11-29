/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:17:40 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 03:01:16 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_struct_exec(t_stock *stock, int i)
{
	stock->exec.cmd = ft_find_cmd_for_exec(stock, i);
	if (!stock->exec.cmd)
		return (1);
	stock->exec.cmd_tab = ft_find_tab(stock, i);
	stock->exec.path = path_to_cmd(stock, &stock->exec, stock->envp);
	stock->exec.env = tab_env(&stock->exec, stock->envp);
	return (0);
}

char	*chr_path(t_stock *stock, t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	stock->exit_status = 127;
	return (NULL);
}

char	*ft_find_cmd_for_exec(t_stock *stock, int i)
{
	t_cmd	*tmp;
	int		compteur;

	compteur = 0;
	tmp = stock->cmd;
	while (tmp)
	{
		if (compteur == i)
		{
			return (tmp->args[0]);
		}
		compteur++;
		tmp = tmp->next;
	}
	return (NULL);
}

char	**ft_find_tab(t_stock *stock, int i)
{
	int		compteur;
	t_cmd	*tmp;

	compteur = 0;
	tmp = stock->cmd;
	while (tmp)
	{
		if (compteur == i)
		{
			if (tmp->args[1])
				return (tmp->args);
		}
		compteur++;
		tmp = tmp->next;
	}
	return (NULL);
}
