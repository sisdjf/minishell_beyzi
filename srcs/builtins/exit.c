/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/11/16 22:12:51 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nb_args_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i++;
	}
	return (i - 1);
}


int	ft_exit(char **cmd)
{
	int	i;

	i = nb_args_exit(cmd);
	printf("i = %d\n", i);
	if (i == 0)
		printf("exit\n");
	if (i == 1)
		check_atoi_exit(cmd);
	if (i == 2)
	{
		printf("exit :  too many arguments\n");
		return (1);
	}
	return (0);
}

// int	ft_exit_fork(char **cmd, t_stock *stock)
// {
// 	int	i;
// 	int pipe;

// 	i = nbr_malloc_word_cmd(stock->token, pipe);
// 	if (i == 0)
// 	{
// 		clear_exit(stock, cmd, pipe);
// 		// exit(stock->status);
// 	}
// 	if (i >= 1)
// 		check_atoi_exit(cmd);
// 	if (i >= 2)
// 	{
// 		ft_printf("exit: too many arguments\n");
// 		return (1);
// 	}
// 	if (cmd[1])
// 	{
// 		// stock->status = ft_atoi(cmd[1]);
// 		clear_exit(stock, cmd, i);
// 	}
// 	clear_exit(stock, cmd, i);
// 	// exit(stock->status);
// }
// void	clear_exit(t_stock *stock, char **cmd, int i)
// {
// 	if (i == 0)
// 	{
// 		close(stock->fd_std[0]);
// 		close(stock->fd_std[1]);
// 	}
// 	if (i == 2)
// 	{
// 		free_tab(cmd);
// 		free_tokens(stock->token);
// 		// exit(stock->status);
// 	}
// 	free_tab(cmd);
// 	free_tokens(stock->token);
// }
