/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:34:09 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/31 21:49:49 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//s = valeur a partir de laquelle extraire la sous chaine
//start = index de debut de la nvl chaine dans la chaine 's'
//len = nombre de caractere dans la sous chaine si
//(suite du len) --> la longueur est = 0 le result et nul

//en gros c comme strnstrn

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (ft_strlen(s) < start)
		len = 0;
	else if (ft_strlen(s) < start + len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}
//quand le i = 7 et que le sous chaine se cree on peut incrementer i
// ton j est = a n (12) une fois arriver a 12 il se stop
//le i lui continue dans la boucle on lui donne 7 pour quils comme a 7

/*int	main(void)
{
	char src[] = "Une sous chaine de caractere";

	int m = 7;
	int n = 12;

	char *dest = ft_substr(src, m, n);
	printf("%s\n", dest);

	return (0);
}*/
