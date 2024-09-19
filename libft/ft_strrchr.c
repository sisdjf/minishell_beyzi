/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:55:42 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/13 19:42:55 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}

/*int	main()
{
	char	str[] = "piscine";
    	printf("%p\n", ft_strrchr(str, 'i' + 256));
	printf("%p\n", strrchr(str, 'i' + 256));

	printf("%p\n", ft_strrchr(str, 'i'));
	printf("%p\n", strrchr(str, 'i'));
}*/
