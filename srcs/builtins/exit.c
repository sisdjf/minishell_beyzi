/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/11/30 21:49:17 by sizitout         ###   ########.fr       */
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

int	ft_exit_fork(t_stock *stock, char **cmd)
{
	int	nb_args;

	nb_args = nb_args_exit(cmd);
	if (nb_args == 0)
	{
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
	}
	if (nb_args == 1)
	{
		stock->exit_status = ft_atoi_exit(cmd[1]);
		check_atoi_exit(stock, cmd);
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		exit(stock->exit_status);
	}
	if (nb_args >= 2)
	{
		ft_printf(" too many arguments\n");
		exit(stock->exit_status = 1);
	}
	exit(0);
}

void	ft_all_free(t_stock *stock)
{
	free_exec(stock);
	free_tokens(&stock->token);
	free_cmd(&stock->cmd);
	ft_free_envp_list(&stock->envp);
	close(stock->fd_std[1]);
	close(stock->fd_std[0]);
}

int	ft_exit(t_stock *stock, char **cmd)
{
	int	nb_args;

	nb_args = nb_args_exit(cmd);
	if (nb_args == 0)
	{
		ft_all_free(stock);
	}
	if (nb_args == 1)
	{
		stock->exit_status = ft_atoi_exit(cmd[1]);
		check_atoi_exit(stock, cmd);
		ft_all_free(stock);
		exit(stock->exit_status);
	}
	if (nb_args >= 2)
	{
		ft_printf(" too many arguments\n");
		ft_all_free(stock);
		exit(stock->exit_status = 1);
	}
	printf("exit\n");
	exit(stock->exit_status);
}

int	printf_exit(t_stock *stock, char *str, int code)
{
	printf("%s", str);
	stock->exit_status = code;
	return (1);
}
