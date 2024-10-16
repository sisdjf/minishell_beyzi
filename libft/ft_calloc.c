/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:07:30 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/15 22:52:04 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buff;
	size_t	i;

	i = 0;
	if (count > sizeof(char) * 2147483424 || size > sizeof(char) * 2147483424)
		return (NULL);
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	buff = (void *)malloc(count * size);
	if (!buff)
		return (NULL);
	while (i < count * size)
	{
		((unsigned char *)buff)[i] = 0;
		i++;
	}
	return (buff);
}
//la fonction calloc alloue la memoire pour un tableau
