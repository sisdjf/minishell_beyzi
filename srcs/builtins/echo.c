/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:03:28 by lybey             #+#    #+#             */
/*   Updated: 2024/11/18 01:41:41 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	arg_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	print_echo(t_stock *stock, char **cmd, int start)
{
	int	i;

	i = start;
	while (cmd[i])
	{
		if (cmd[i][0] == '$' && cmd[i][1] == '?')
			printf("%d", stock->exit_status);
		else
			printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	if (start == 1)
		printf("\n");
	return (0);
}

int	check_n_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			j = 1;
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'n' && cmd[i][j] != '\0')
					return (i);
				j++;
			}
		}
		else
			return (i);
		j = 0;
		i++;
	}
	return (i);
}
int	echo(t_stock *stock, char **cmd)
{
	int i;
	int nb_arg;

	i = 0;
	nb_arg = arg_len(cmd);
	if (nb_arg == 1)
		printf("\n");
	else if (i < nb_arg)
	{
		i = check_n_option(cmd);
		print_echo(stock, cmd, i);
	}
	return (0);
}