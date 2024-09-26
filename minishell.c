/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/26 21:47:06 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token			*token;
	static t_stock	stock = {0};

	// t_stock			*stock;
	token = NULL;
	ft_bzero(&token, sizeof(token));
	if (argc == 1)
		(void)envp;
	// (void)argv;
	// (void)argc;
	// if(pwd(argv) == 0)
	// 	printf("ok\n");
	
	while (1)
	{
		ft_prompt(&stock, *argv);
	}
	return (0);
}
