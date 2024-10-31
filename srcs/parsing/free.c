/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:10:10 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/31 23:12:18 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_envp(t_envp *envp)
{
	if (envp)
	{
		if (envp->env_str)
			free(envp->env_str);
		if (envp->key)
			free(envp->key);
		if (envp->value)
			free(envp->value);
		free(envp);
	}
}

void	ft_free_envp_list(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		tmp = envp->next;
		free_envp(envp);
		envp = tmp;
	}
}
