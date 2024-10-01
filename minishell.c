/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/01 23:52:14 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_strlen_du_nbr_de_str(char **envp)
// {
// 	int i;

// 	i = 0;
// 	while(envp[i])
// 	{
// 		i++;
// 	}
// 	return(i);
// }

// void ft_copy_env_tab(char **envp, t_stock *stock)
// {
// 	int i;
// 	int size;

// 	i = 0;
// 	size = ft_strlen_du_nbr_de_str(envp);
// 	stock->env = malloc((sizeof(char *) * size) + 1);
// 	while(envp[i])
// 	{
// 		stock->env[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	stock->env[i] = NULL;
// }

int	main(int argc, char **argv, char **env)
{
	static t_stock	stock = {0};
	stock_env_lst(env, &stock);
	(void)argc;
	while (1)
	{
		ft_prompt(&stock, *argv);
	}
	return (0);
}





	// str = malloc(20);
	// str = ft_strdup("$LESS");