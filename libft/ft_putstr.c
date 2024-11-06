/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:57:52 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/06 02:47:09 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str, int *len)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*len) = *len + 6;
		return (0);
	}
	write(1, str, strlen(str));
	(*len) += strlen(str);
	return (i);
}
