/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:26:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 23:29:06 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*to_next_double_q(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*double_quote(char *str, int *i, t_stock *data)
{
	char	*env_str;

	env_str = NULL;
	(*i)++;
	env_str = ft_joinstr(env_str, ft_strdup("\""));
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			env_str = ft_joinstr(env_str, after_env_str(data, str, i));
		else
			env_str = ft_joinstr(env_str, to_next_double_q(str, i));
	}
	(*i)++;
	return (ft_joinstr(env_str, ft_strdup("\"")));
}
