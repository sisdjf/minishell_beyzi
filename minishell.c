/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/16 01:26:12 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	static t_stock	stock= {0};
	(void)argc;
	stock_env_lst(env, &stock);
	ft_prompt(&stock, *argv);
	ft_free_envp_list(stock.envp);
	free_tokens(stock.token);
	return (0);
}
