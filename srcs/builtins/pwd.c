/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:11:36 by lybey             #+#    #+#             */
/*   Updated: 2024/11/27 22:19:37 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(char **cmd)
{
	char	*str;

	if (arg_len(cmd) > 1 && cmd[1][0] == '-')
		return (ft_printf("pwd : pas d'option\n"));
	str = getcwd(NULL, 0);
	if (!str)
	{
		printf("pwd: error retrieving current directory: getcwd:");
		printf("cannot access parent directories: No such file or directory\n");
	}
	else
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
