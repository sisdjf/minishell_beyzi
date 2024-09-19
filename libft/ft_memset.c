/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:34:16 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/24 17:21:28 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//s = (ptr)debut de la zone de memoire sur une adresse
//c = valeur pour remplir la zone de memoire
//n = nombre d'octect a mettre en marche
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*p;
	unsigned char	valeur;

	i = 0;
	p = s;
	valeur = (int)c;
	while (n > 0)
	{
		p[i] = valeur;
		i++;
		n--;
	}
	return (s);
}
/*int	main(void)
{
	int arr[10];
	printf("%p", ft_memset(arr, 4, sizeof(arr)));
}*/