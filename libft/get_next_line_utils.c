/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:18:34 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:44:37 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlengnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}


char	*ft_strjoingnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlengnl(s1) + ft_strlengnl(s2)) + 1);
	if (!s)
		return (NULL);
	if (s2)
	{
		while (s2[i] != '\0')
		{
			s[i] = s2[i];
			i++;
		}
	}
	while (s1[++j] != '\0')
		s[i + j] = s1[j];
	if (s2)
		free(s2);
	s[i + j] = '\0';
	return (s);
}

int	get_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
