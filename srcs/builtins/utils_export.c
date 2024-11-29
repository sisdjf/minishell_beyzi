/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:11:54 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 02:13:17 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!(tmp->value))
		{
			printf("export %s\n", tmp->key);
		}
		else
		{
			printf("export %s=\"%s\"\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}

char	*get_key_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (ft_strdup(str));
}
