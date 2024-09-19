/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:06:40 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/27 14:07:17 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//copier une zone de memoire
//dest = specifie l'add du bloc et copie les donnees
//src = definir l'add du bloc a dupliquer
//n = nombre doctet a dupp 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*tdest;
	const char	*tsrc;

	tdest = dest;
	tsrc = src;
	while (n-- > 0)
		*tdest++ = *tsrc++;
	return (dest);
}
/*int	main(int agrc, char** argv)
{
	char	str[] = "start stop";
	printf("%s\n", str);
	
ft_memcpy(str, str + 6, 4 * sizeof(char));

	return (0);
}*/
/*int	main()
{
	char src[]= "hello";
	char dest[13];
	
	ft_memcpy(dest, src, 5);
	printf("dest apres les premier ft_memcpy()=> %s\n", dest);
	
	ft_memcpy(dest + sizeof(src)-1, "world", 7);
	printf("dest apres les second ft_memcpy()=> %s\n", dest);

	return (0);
}*/
