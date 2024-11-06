/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:08:21 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/07 00:10:53 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char c, va_list *args, int *len)
{
	if (c == 'c')
		ft_putchar(va_arg(*args, int), len);
	if (c == 's')
		ft_putstr(va_arg(*args, char *), len);
	if (c == 'p')
		ft_putptr(va_arg(*args, void *), len);
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(*args, int), len);
	if (c == 'u')
		ft_putnbrpo(va_arg(*args, unsigned int), len);
	if (c == 'x' || c == 'X')
		ft_puthex(va_arg(*args, unsigned int), c, len);
	if (c == '%')
		ft_putchar('%', len);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		len;

	va_start(args, str);
	i = 0;
	len = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			ft_check(str[i + 1], &args, &len);
			i++;
		}
		else if (str[i] == '%' && str[i + 1] == '\0')
			return (-1);
		else
			ft_putchar(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
