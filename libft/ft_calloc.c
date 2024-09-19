/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:07:30 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/30 19:30:36 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*cal;

	if (count != 0 && ((count * size) / count != size))
		return (NULL);
	cal = malloc(count * size);
	if (!cal)
		return (NULL);
	ft_memset(cal, 0, count * size);
	return (cal);
}

//la fonction calloc alloue la memoire pour un tableau
