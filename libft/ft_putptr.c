/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:47:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:23:12 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned long int nb, char *base, int *len)
{
	if (nb >= 16)
	{
		ft_putnbr_base(nb / 16, base, len);
	}
	ft_putchar(base[nb % 16], len);
}

int	ft_putptr(void *ptr, int *len)
{
	unsigned long long int	n;

	n = (unsigned long long int)ptr;
	if (n == 0)
		return (ft_putstr("(nil)", len));
	ft_putstr("0x", len);
	ft_putnbr_base(n, "0123456789abcdef", len);
	return (0);
}
// int	main(void)
// {
// 	int	c;
// 	int	*ptr;

// 	c = 10;
// 	ptr = &c;
// 	ft_putstr("mon : ");
// 	ft_putptr(ptr);
// 	printf("\nvrai: %p\n", (void *)ptr);
// 	return (0);
// }
