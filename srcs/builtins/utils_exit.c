/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:40:06 by lybey             #+#    #+#             */
/*   Updated: 2024/11/18 01:32:42 by sizitout         ###   ########.fr       */
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
int	check_atoi_exit(t_stock *stock, char **cmd)
{
	int	i;

	i = 0;
	// printf("%s", cmd[1]);
	while (cmd[1][i])
	{
		if ((cmd[1][i] == '-' || cmd[1][i] == '+') && i == 0)
			i++;
		if (!ft_isdigit(cmd[1][i]))
		{
			// printf("{%c}\n i = {%d}\n", cmd[1][i], i);
			// printf("exit : %s :  numeric argument required\n", cmd[1]);
			ft_printf(" numeric argument required\n");
			return (stock->exit_status = 2);
		}
		i++;
	}
	if (ft_atoi_exit(cmd[1]) == 0)
	{
		ft_printf("exit : %s : numeric argument required------------\n",
				cmd[1]);
		return (stock->exit_status = 1);
	}
	return (0);
}
