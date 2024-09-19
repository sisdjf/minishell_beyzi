/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:28:11 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/25 21:13:56 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//recherche caracte dans une zone de memoire tmp

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;

	i = 0;
	str = (const unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char s1[14] = "sirine";
	const char	s2[] = ft_memchr(s1, 's', 6);
	printf(s2[1] = "%c\n");
}*/

/*int main()
{
    char str1[50] = "Je suis Sirine";
    printf("%s\n", memchr(str1));
}*/

/*int	main(void)
{
	printf("%p\n", ft_memchr("12345", '4', 7));
	printf("%p\n", memchr("12345", '4', 5));
	return (0);

}*/
