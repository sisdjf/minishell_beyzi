/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 20:07:30 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/10 00:17:40 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*cal;

// 	if (count != 0 && ((count * size) / count != size))
// 		return (NULL);
// 	cal = malloc(count * size);
// 	if (!cal)
// 		return (NULL);
// 	ft_memset(cal, 0, count * size);
// 	return (cal);
// }
void	*ft_calloc(size_t count, size_t size)
{
	char	*s;

	if (size && (count > SIZE_MAX / size))
		return (NULL);
	s = malloc(size * count);
	if (!s)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}
//la fonction calloc alloue la memoire pour un tableau
