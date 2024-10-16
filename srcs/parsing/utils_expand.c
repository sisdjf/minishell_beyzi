/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/16 20:27:27 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dd_quote(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_quotes_expand(t_stock *stock, char *str, int *i)
{
	char	*str_quote;
	int		start;

	str_quote = NULL;
	start = *i;
	if (str[*i] == SQUOTE)
	{
		(*i)++;
		while (str[*i] && str[*i] != SQUOTE)
			(*i)++;
		(*i)++;
		return (ft_substr(str, start, *i - start));
	}
	// str_quote = ft_joinstr(str_quote, ft_strdup("\'"));
	while (str[*i] != DQUOTE)
	{
		if (str[*i] == '$')
		{
			str_quote = ft_joinstr(str_quote, after_env_str(stock, str, i));
		}
		else
			str_quote = ft_joinstr(str_quote, dd_quote(str, i));
		(*i)++;
	}
	(*i)++;
	return (ft_strjoin(str_quote, ft_strdup("\'")));
}

char	*all_dollar(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
