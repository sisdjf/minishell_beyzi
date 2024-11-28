/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/28 03:35:58 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*dd_quote(char *str, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (str[*i] && str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	new = ft_substr(str, start, *i - start);
	return (new);
}

char	*ft_quotes_expand(t_stock *stock, char *str, int *i)
{
	char	*str_quote;
	int		start;

	(void)stock;
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
	(*i)++;
	return (ft_joinstr(str_quote, ft_strdup("\"")));
}

char	*all_dollar(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\'')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

int	norm_quote(char *str, int i)
{
	int	count;

	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	return (count % 2);
}

char	*bool_not_expand(char *str)
{
	char	*str_expand;

	str_expand = delete_quote(str);
	free(str);
	return (str_expand);
}
