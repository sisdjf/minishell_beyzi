/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/27 01:02:30 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp *lst_env)
{
	int		i;
	t_envp	*new_env;
	char	*egal;

	i = 0;
	while (lst_env->env[i])
	{
		new_env = malloc(sizeof(t_envp));
		if (!new_env)
			return ;
		new_env = lst_env->env;
		egal = ft_strchr(lst_env->env[i], '=');
		if (egal)
		{
			egal[1] = '\0';
			printf("%s\n", egal);
		}
		printf("%s\n", new_env);
	}
}

//A REVOIR POUR DEMAIN

void	print_envp(char **env)
{
	int i = 0;
	// if (env == NULL)
	// {
	// 	printf("NULL\n");
	// 	return ;
	// }
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}