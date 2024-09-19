/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:32:34 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/27 14:11:50 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	char	*strlittle;
	size_t	i;
	size_t	j;

	str = (char *)big;
	strlittle = (char *)little;
	if (!*strlittle)
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == strlittle[j] && (i + j < len))
		{
			if (strlittle[j + 1] == '\0')
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*{
	/char	*str;
	char	*lstr;
	int		i;
	int		j;
	int		little_length;

	i = 0;
	j = 0;
	str = (char *)big;
	if (!str)
		return (NULL);
	if (!little)
		return (str);
	lstr = (char *)little;
	little_length = ft_strlen(lstr);
	while (str[i] != '\0' && i < len)
	{
		if (str[i] != little[j])
			i++;
		else
		{
			while (little[j] != '\0' && i < len)
			{
				if (big[i] != little[j])
					break ;
				i++;
				j++;
			}
			if (j == little_length)
				return (&str[i - little_length]);
			else
				j = 0;
		}
	}
	return (NULL);
}*/

/*int	main(void)
{
	char	*s;
	char	*cherche;

	// strnstr
	s = "Sirine fait du pseudo code";
	cherche = "fai";
	printf("\n---- strnstr ----\n");
	printf("myfunc : %s", ft_strnstr(s, cherche, 19));
	// printf("\nrealfunc : %s", strnstr(s, cherche, 19));
	return (0);
}*/