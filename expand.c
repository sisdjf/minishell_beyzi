/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:40:08 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/08 17:55:12 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				// printf(" FIND_VALUE : %s\n", tmp->value);
				return (tmp->value);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_value_new(t_stock *stock, char *str, int *i)
{
	char	*key;
	char	*value;
	int		k;
	int		size;
	int		j;

	j = 0;
	k = *i;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '_'))
		k++;
	size = k - *i;
	key = malloc(sizeof(char) * (size) + 1);
	if (!key)
		return (NULL);
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		key[j] = str[*i];
		(*i)++;
		j++;
	}
	key[j] = '\0';
	value = find_value(stock->envp, key);
	// printf("variable value : %s\n", value);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
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
	}
	free(str);
	return (str_env);
}

void	ft_expand(t_stock *stock, t_token *token)
{
	t_token	*tmp;
	char	*pos_dollar;
	char	*key_start;
	char	*end;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		pos_dollar = ft_strchr(tmp->name, '$');
		if (pos_dollar)
		{
			// printf("pos_dollar : %s\n", pos_dollar);
			key_start = pos_dollar + 1;
			// printf("key_start : %s\n", key_start);
			end = key_start;
			// printf("END : %s\n", end);
			tmp->name = bool_expand(stock, tmp->name);
			// printf(" FT_EXPAND-bool expand : %s\n", tmp->name);
			while (*end && (ft_isalnum(*end) || *end == '_'))
			{
				end++;
			}
			// find_value(stock->envp, key_start);
			printf("FT_EXPAND : %s\n", tmp->name);
		}
		tmp = tmp->next;
	}
}

// void	ft_expand(t_envp *env, char *key_start)
// {
// 	while (env)
// 	{
// 		if (ft_strcmp(env->key, key_start) == 0) // strncmp
// 		{
// 			if (env->value)
// 			{
// 				printf("%s\n", env->value);
// 			}
// 			return ;
// 		}
// 		env = env->next;
// 	}
// 	printf("\n"); //A GERER DANS LE ECHO
// }

// void	chr_dollar(t_stock *stock, t_token *token)
// {
// 	char *pos_dollar;
// 	char *key_start;
// 	char *end;

// 	while (token) //->type : cd
// 	{
// 		pos_dollar = ft_strchr(token->name, '$');
// 		if (pos_dollar)
// 		{
// 			printf("----%s\n", pos_dollar);
// 			key_start = pos_dollar + 1;
// 			end = key_start;
// 			while (*end && (ft_isalnum(*end) || *end == '_'))
// 			{
// 				end++;
// 			}
// 			// char *after = end;
// 			printf(" OKKKK%c\n", *end);
// 			*end = '\0';
// 			// while (*after)
// 			// {
// 			// 	if(!ft_isalnum(*after) && *after != '_')
// 			// 	{
// 			// 		printf("%c", *after);
// 			// 	}
// 			// 	after++;
// 			// }
// 				ft_expand(stock->envp, key_start); //
// 				// if (stock->envp)
// 				// {
// 				// 	ft_expand(stock->envp,);
// 				// 	printf("LE DOLLAR: %s\n", token->name);
// 				// }
// 			}
// 			token = token->next;
// 		}
// 	}
