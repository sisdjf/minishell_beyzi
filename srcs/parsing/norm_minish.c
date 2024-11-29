/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_minish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:19:35 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 23:27:46 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_signal(void)
{
	signal(SIGINT, &ft_gestion);
	signal(SIGQUIT, SIG_IGN);
}

int	event_hook(void)
{
	return (EXIT_SUCCESS);
}

void	init_stock(t_stock *stock)
{
	g_globale = 0;
	stock->signal = 0;
	stock->nb_hd = 0;
	stock->token = NULL;
	stock->cmd = NULL;
}
