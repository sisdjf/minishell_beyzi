/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/11/25 20:16:26 by sizitout         ###   ########.fr       */
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

int	ft_exit(t_stock *stock, char **cmd)
{
	int	nb_args;

	nb_args = nb_args_exit(cmd);
	// ft_printf("exit");
	if (nb_args == 0)
	{
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		// close_fds(stock);
		exit(stock->exit_status);
	}
	if (nb_args == 1)
	{
		stock->exit_status = ft_atoi_exit(cmd[1]);
		// printf("avant exit %d\n", stock->exit_status);
		check_atoi_exit(stock, cmd);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		// close_fds(stock);
		exit(stock->exit_status);
	}
	if (nb_args >= 2)
	{
		ft_printf(" too many arguments\n");
		exit (stock->exit_status = 1);
	}
	exit (0);
}
