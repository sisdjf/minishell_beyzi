/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:19:35 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:20:33 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_sigint(int signum)
{
	g_globale = 128 + signum;
	rl_done = 1;
}

void	handle_signal(void)
{
	signal(SIGINT, &if_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

int	event_hook(void)
{
	return (EXIT_SUCCESS);
}

void	init_stock(t_stock *stock)
{
	stock->signal = 0;
	stock->token = NULL;
	stock->cmd = NULL;
}
