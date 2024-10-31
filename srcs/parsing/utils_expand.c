/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/21 21:56:40 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return (ft_joinstr(str_quote, ("\"")));
}

char	*all_dollar(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
