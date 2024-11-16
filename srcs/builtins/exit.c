/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/11/16 18:45:25 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit_status(t_stock *stock)
{
	
	return(stock->exit_status);
}

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
	if (nb_args == 0)
	{
		printf("exit\n");
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		close_fds(stock);
		exit(0);
	}
	if (nb_args == 1)
	{
		check_atoi_exit(cmd);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		close_fds(stock);
		exit(check_atoi_exit(cmd));
	}
	if (nb_args >= 2)
	{
		printf("exit :  too many arguments\n");
		return (1);
	}
	return (0);
}
