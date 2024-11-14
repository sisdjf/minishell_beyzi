/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/13 21:03:36 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_value(t_envp *env, char *key_start)
{
	t_envp	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key_start) == 0)
		{
			if (tmp->value)
				return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_value_new(t_stock *stock, char *str, int *i)
{
	int	k;
	int	size;
	int	j;

	j = 0;
	k = *i;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '_'))
		k++;
	size = k - *i;
	stock->key = ft_calloc((size) + 1, sizeof(char));
	if (!stock->key)
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		stock->key[j] = str[*i];
		(*i)++;
		j++;
	}
	stock->key[j] = '\0';
	stock->value = find_value(stock->envp, stock->key);
	free(stock->key);
	if (!stock->value)
		return (ft_strdup(""));
	return (ft_strdup(stock->value));
}

char	*after_env_str(t_stock *stock, char *str, int *i)
{
	char	*env;

	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if ((str[*i] == '\'' || str[*i] == '"') && !norm_quote(str, *i))
		return (ft_strdup(""));
	if ((!ft_isalpha(str[*i]) && str[*i] != '_'))
		return (ft_strdup("$"));
	env = find_value_new(stock, str, i);
	return (env);
}
// char	*all_dollar2(char *str, int *i)
// {
// 	int	start;

// 	start = *i;
// 	while (str[*i] && str[*i] != '$' && str[*i] != '"')
// 		(*i)++;
// 	return (ft_substr(str, start, *i - start));
// }

// char	*ft_quotes_expand_dquote(t_stock *stock, char *str, int *i)
// {
// 	char *str_quote = NULL;

// 	(void)stock;
// 	str_quote = ft_joinstr(str_quote, ft_strdup("\""));
// 	(*i)++;
// 	while (str[*i] && str[*i] != DQUOTE)
// 	{
// 		if (str[*i] != '$')
// 			str_quote = ft_joinstr(str_quote,  dd_quote(str, i));
// 		else
// 			str_quote = ft_joinstr(str_quote,  after_env_str(stock, str, i));
// 	}
// 	str_quote = ft_joinstr(str_quote, ft_strdup("\""));
// 	(*i)++;
// 	return (str_quote);
// }

char	*bool_expand(t_stock *stock, char *str)
{
	char	*str_env;
	char	*test;
	int		i;

	i = 0;
	str_env = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			str_env = ft_joinstr(str_env, ft_quotes_expand(stock, str, &i));
		}
		else if (str[i] && str[i] == '$')
		{
			str_env = ft_joinstr(str_env, after_env_str(stock, str, &i));
		}
		else
		{
			str_env = ft_joinstr(str_env, all_dollar(str, &i));
		}
		if (i > ft_strlen_check(str))
			break ;
	}
	free(str);
	test = delete_quote(str_env);
	free(str_env);
	return (test);
}

void	ft_expand(t_stock *stock, t_token *token)
{
	t_token	*tmp;
	char	*pos_dollar;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		pos_dollar = ft_strchr(tmp->name, '$');
		if (pos_dollar)
		{
			tmp->name = bool_expand(stock, tmp->name);
		}
		else
		{
			tmp->name = bool_not_expand(tmp->name);
		}
		tmp = tmp->next;
	}
}
