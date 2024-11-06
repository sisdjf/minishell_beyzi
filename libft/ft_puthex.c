/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:47:36 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:23:00 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned int nb, char c, int *len)
{
	char	*min;
	char	*maj;

	min = "0123456789abcdef";
	maj = "0123456789ABCDEF";
	if (nb > 15)
	{
		ft_puthex(nb / 16, c, len);
		ft_puthex(nb % 16, c, len);
	}
	if (nb < 16)
	{
		if (c == 'x')
		{
			write(1, &min[nb], 1);
			(*len)++;
		}
		else
		{
			write(1, &maj[nb], 1);
			(*len)++;
		}
	}
	return (1);
}
