/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:52:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/17 00:21:18 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_len_mini(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*ft_joinstr(char *s1, char *s2)
{
	int		i;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	res = malloc(ft_len_mini(s1) + ft_len_mini(s2) + 1);
	if (!res)
		return (NULL);
	while (i < ft_len_mini(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < ft_len_mini(s1) + ft_len_mini(s2))
	{
		res[i] = s2[i - ft_len_mini(s1)];
		i++;
	}
	res[i] = 0;
	free(s1);
	free(s2);
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	print_tab(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s ", tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
}


void	ft_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (path != NULL)
		printf("path=%s\n", path);
}
