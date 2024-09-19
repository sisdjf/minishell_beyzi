/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:28:26 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/24 16:02:28 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//comme memcpy mais sa se chevauche, on perd pas les octets

void	*ft_memmove(void *destina, const void *source, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*src;
	size_t				i;

	if (destina == NULL && source == NULL)
		return (0);
	i = 0;
	dest = (unsigned char *)destina;
	src = (const unsigned char *)source;
	if (src < dest)
	{
		while (n--)
		{
			dest[n] = src[n];
		}
	}
	else
	{
		while (n > i)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}

/*int	main(int agrc, char** argv)
{
	char	str[] = "startuuuuuuu stop";
	printf("%s\n", str);
	
	memmove(str, str + 6, 4 * sizeof(char));

	return (0);
}*/
/*int main()
{
    char dest[] = "Hello";
    const char src[] = "World";

    printf("Avant memove dest = %s, src = %s\n, dest, src");
    ft_memmove(dest, src, 10);
    printf("Apres memove dest = %s, src = %s\n, dest, src");

    return (0);
}*/
