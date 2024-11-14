/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/11/14 21:30:35 by sizitout         ###   ########.fr       */
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
