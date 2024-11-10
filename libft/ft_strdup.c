/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:19:28 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/10 18:44:25 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_len(src);
	dest = ft_calloc(sizeof(char), len + 1);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*size_t  ft_strlen(char *str)
{
    size_t  i;

    
    i = 0;
    while (str[i])
    i++;
    return (i);    
}

char	*ft_strdup(const char *src)
{
	char	*str;
	char	*src_casted;
	size_t	i;

	str = malloc(sizeof(char) * ft_strlen((char)*src) + 1);
	if (!str)
		return (0x0);
	src_casted = (char *)src;
	i = 0;
	while (src_casted[i] != '\0')
	{
		str[i] = src_casted[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}*/
/*int	main(void)
{
	char s1[13] = "coucou";
	char *p;
	p = ft_strdup(s1);
	printf("%s\n", s1);
	printf("%s\n", p);
}*/