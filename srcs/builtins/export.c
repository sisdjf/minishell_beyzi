/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:58:44 by lybey             #+#    #+#             */
/*   Updated: 2024/11/30 00:02:58 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_strdup(str + i + 1));
		i++;
	}
	return (NULL);
}

int	check_export(char *key)
{
	int	i;

	i = 0;
	if (!key[i] || (!ft_isalpha(key[i]) && key[i] != '_'))
		return (ft_printf("bash: export: `%s': not a valid identifier\n", key),
			1);
	while (key[i])
	{
		if (ft_isalnum(key[i]) || key[i] == '_')
			i++;
		else
		{
			ft_printf("bash: export:`%s': not a valid idetifier\n", key);
			return (1);
		}
	}
	return (0);
}

int	add_to_env(char *key, char *value, t_envp **envp)
{
	int		i;
	char	*str;
	char	*mini;
	t_envp	*to_replace;

	i = 0;
	if (check_export(key))
		return (free(value), 1);
	to_replace = search_envp(*envp, key);
	if (to_replace && value)
	{
		free(to_replace->value);
		to_replace->value = value;
	}
	else if (!to_replace)
	{
		str = ft_strjoin(key, "=");
		mini = ft_strjoin(str, value);
		free(value);
		free(str);
		ft_lstadd_back_envp(envp, ft_lstnew_envp(mini));
		free(mini);
	}
	return (0);
}

int	export(char **cmd, t_envp **envp)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '='))
		{
			i++;
			continue ;
		}
		key = get_key_export(cmd[i]);
		value = get_value_export(cmd[i]);
		add_to_env(key, value, envp);
		free(key);
		i++;
	}
	return (0);
}
