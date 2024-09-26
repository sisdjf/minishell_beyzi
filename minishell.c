/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/26 18:59:15 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token			*token;
	static t_stock	stock = {0};

	// t_stock			*stock;
	token = NULL;
	// ft_bzero(&token, sizeof(token));
	if (argc == 1)
		(void)envp;
	// (void)argv;
	// (void)argc;
	while (1)
	{
		ft_prompt(&stock, *argv);
	}
	ft_path();
	return (0);
}
