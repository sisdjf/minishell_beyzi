/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrpo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:46:51 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:23:09 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrpo(unsigned int nb, int *len)
{
	if (nb <= 9)
	{
		ft_putchar(nb + '0', len);
	}
	else
	{
		ft_putnbrpo(nb / 10, len);
		ft_putchar(nb % 10 + '0', len);
	}
}
// int	main(void)
// {
// 	ft_putnbrpo(49999999);
// 	return (0);
// }