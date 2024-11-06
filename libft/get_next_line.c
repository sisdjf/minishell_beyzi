/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:17:46 by sizitout          #+#    #+#             */
/*   Updated: 2024/01/24 16:42:22 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_line(char *bufs)
{
	int	i;

	i = 0;
	while (bufs && bufs[i])
	{
		if (bufs[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_line(int fd, char *stash)
{
	char	*buffer;
	int		rd;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd < 0)
			return (free(buffer), NULL);
		buffer[rd] = '\0';
		stash = ft_strjoingnl(buffer, stash);
		if (check_line(stash))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	int		i;
	char	*res;

	i = 0;
	if (!*stash)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlengnl(stash) + 1));
	if (!res)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
	{
		res[i] = stash[i];
		i++;
	}
	if (stash[i])
	{
		res[i] = '\n';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*clear_stash(char *stash)
{
	char	*str;
	int		stashlen;
	int		i;
	int		totallen;

	stashlen = get_index(stash);
	totallen = ft_strlengnl(stash) - get_index(stash);
	i = 0;
	if (!totallen)
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (totallen + 1));
	if (!str)
		return (NULL);
	while (stash[stashlen] != '\0')
	{
		str[i] = stash[stashlen];
		i++;
		stashlen++;
	}
	str[i] = '\0';
	free(stash);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_line(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = clear_stash(stash);
	if (!line)
		free(stash);
	return (line);
}
