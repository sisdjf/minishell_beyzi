/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 00:29:49 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/28 00:48:19 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	chr_equal(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// t_envp	*ft_lstnew_envp(char *env_str)
// {
// 	t_envp	*new;

// 	new = malloc(sizeof(t_envp));
// 	if (!new)
// 		return (NULL);
// 	new->env_str = ft_strdup(env_str);
// 	new->before = ft_substr(env_str, 0, chr_equal(env_str));
// 	new->after = ft_substr(env_str, (chr_equal(env_str) + 1),
// 			ft_strlen(env_str));
// 	return (new);
// }

// void	ft_lstadd_back_envp(t_envp **token, t_envp *new)
// {
// 	t_envp	*last;

// 	last = *token;
// 	if (*token)
// 	{
// 		while (last->next != NULL)
// 			last = last->next;
// 		last->next = new;
// 	}
// 	else
// 		*token = new;
// }

// void	stock_env_lst(char **env, t_stock *stock)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		ft_lstadd_back_envp(&stock->envp, ft_lstnew_envp(env[i]));
// 		i++;
// 	}
// }

// void	print_lst_envp(t_stock *stock)
// {
// 	while (stock->envp)
// 	{
// 		printf("Before -> %s\n", stock->envp->before);
// 		printf("After -> %s\n", stock->envp->after);
// 		stock->envp = stock->envp->next;
// 	}
// }
void	print_envp(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}