/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:40:06 by lybey             #+#    #+#             */
/*   Updated: 2024/11/16 22:11:46 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi_exit(char *str)
{
	int			i;
	int			sign;
	long int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if ((res > INT_MIN) && (res < INT_MAX))
		return (res * sign);
	else
		return (0);
}
int	check_atoi_exit(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[1][i])
	{
		if ((cmd[1][i] == '-' || cmd[1][i] == '+') && i == 0)
			i++;
		if (!ft_isdigit(cmd[1][i]))
		{
			printf("{%c}\n i = {%d}\n", cmd[1][i], i);
			printf("exit : %s :  numeric argument required\n", cmd[1]);
			exit(2);
		}
		i++;
	}
	if (ft_atoi_exit(cmd[1]) == 0)
	{
		printf("exit : %s : numeric argument required------------\n", cmd[1]);
		exit(2);
	}
	return (0);
}

void	ft_free_exit_no_fork(t_stock *stock)
{
	close(stock->fd_std[0]);
	close(stock->fd_std[1]);
}

