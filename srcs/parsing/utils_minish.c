/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minish.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:55:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:14:35 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_globale;

t_stock	*starton(void)
{
	static t_stock	stock = {0};

	return (&stock);
}

void	ft_gestion(int signum)
{
	t_stock	*stock;

	stock = starton();
	if (signum == SIGINT)
	{
		g_globale = 130;
		rl_done = 1;
	}
	else if (signum == SIGQUIT)
	{
		g_globale = 131;
		rl_done = 1;
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
	}
}

int	handle_syntax_error_and_continue(t_stock *stock, char *input)
{
	if (syntax_error(stock, input))
	{
		free(input);
		return (1);
	}
	return (0);
}

void	cleanup_execution(t_stock *stock, char **input)
{
	if (stock->signal == 128 + SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (stock->signal == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	free_tokens(&stock->token);
	free(*input);
	free_cmd(&stock->cmd);
}
