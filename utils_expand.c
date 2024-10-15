/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/15 22:56:22 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dd_quote(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_quotes_expand(t_stock *stock, char *str, int *i)
{
	char	*str_quote;
	int		start;

	str_quote = NULL;
	start = *i;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
	str_quote = ft_joinstr(str_quote, ft_strdup("\'"));
	(*i)++;
	while (str[*i] != '\'')
	{
		if (str[*i] == '$')
		{
			str_quote = ft_joinstr(str_quote, after_env_str(stock, str, i));
		}
		else
			str_quote = ft_joinstr(str_quote, dd_quote(str, i));
	}
	(*i)++;
	return (ft_strjoin(str_quote, ft_strdup("\"")));
	return (NULL);
}

char	*all_dollar(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
