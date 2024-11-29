/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:50:41 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 00:03:07 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_nodenv(t_envp *env)
{
	free(env->env_str);
	free(env->key);
	free(env->value);
	free(env);
}

t_envp	*search_envp(t_envp *envp, char *key)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if ((ft_strlen(key) == ft_strlen(tmp->key)) && !ft_strncmp(tmp->key,
				key, ft_strlen(tmp->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	unset_loop(char **cmd, t_envp *envp)
{
	t_envp	*to_unset;
	t_envp	*tmp;
	int		i;

	i = 1;
	while (cmd[i])
	{
		tmp = envp;
		to_unset = search_envp(envp, cmd[i]);
		i++;
		if (!to_unset)
			continue ;
		if (tmp == to_unset)
			envp = envp->next;
		while (tmp && tmp != to_unset)
		{
			if (tmp->next && tmp->next == to_unset)
			{
				tmp->next = to_unset->next;
				free_nodenv(to_unset);
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	ft_unset(char **cmd, t_envp *envp)
{
	if (arg_len(cmd) < 2)
		return (printf("no variable to be deleted\n"), 0);
	else
		unset_loop(cmd, envp);
	return (0);
}
