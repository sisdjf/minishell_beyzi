/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:58:57 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:23:05 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb, int *len)
{
	long long int	nbr;

	nbr = nb;
	if (nbr == INT_MIN)
	{
		ft_putstr("-2147483648", len);
		return ;
	}
	if (nb < 0)
	{
		nb = nb * -1;
		ft_putchar('-', len);
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10, len);
	}
	ft_putchar((nb % 10) + '0', len);
}
