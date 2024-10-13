/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/13 03:48:13 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_last(char *str, int i)
{
	int cmpt;

	cmpt = 0;
	while(str[i])
	{
		if(str[i] == '"')
			cmpt++;
		i++;
	}
	return(cmpt % 2);
}
char	*all_dollar(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

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
	stock->key = malloc(sizeof(char) * (size) + 1);
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
	if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	if(str[*i] == '\'' || str[*i] == '"')
		return(ft_strdup(""));
	if ((!ft_isalpha(str[*i]) && str[*i] != '_') /*&& !double_last(str, *i)*/)
		return (ft_strdup("$"));
	env = find_value_new(stock, str, i);
	// printf("variable ENV : %s\n", env);
	return (env);
}

char	*bool_expand(t_stock *stock, char *str)
{
	char	*str_env;
	int		i;

	i = 0;
	str_env = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			str_env = ft_joinstr(str_env, after_env_str(stock, str, &i));
			// printf("BOOL_EXPAND : %s\n", str_env);
		}
		else
			str_env = ft_joinstr(str_env, all_dollar(str, &i));
		// i++;
	}
	free(str);
	return (str_env);
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
		tmp = tmp->next;
	}
}
