/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:57:24 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/24 17:27:47 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
}
//Applique la fonction ’f’ à chaque caractère de la
//chaîne de caractères transmise comme argument,
//et en passant son index comme premier argument.
//Chaque caractère est transmis par adresse à ’f’
//afin d’être modifié si nécessaire.