/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:20:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/20 22:37:06 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
	{
		return (NULL);
	}
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (0);
}

/*int	main(void)
{
	char	str[];

	str[] = "piscine";
	printf("%d\n", ft_strchr(str, 'i' + 256));
	printf("%d\n", strchr(str, 'i' + 256));
	printf("%d\n", ft_strchr(str, 'i'));
	printf("%d\n", strchr(str, 'i'));
}*/
