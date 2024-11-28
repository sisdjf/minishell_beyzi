/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/11/27 22:10:11 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_args_cd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		i++;
	}
	if (i > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (0);
	}
	return (1);
}

char	*find_env_var(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			return ((tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_cd(char **cmd, t_envp **envp)
{
	int		ret;
	char	*path;
	char	**for_export;

	if (!check_args_cd(cmd))
		return (0);
	if (!cmd[1])
	{
		path = find_env_var(*envp);
		if (!path)
			return (0);
	}
	else
		path = cmd[1];
	ret = chdir(path);
	if (ret == -1)
		return (printf("cd : [%s]: No such file or directory\n", cmd[1]), 1);
	for_export = malloc(sizeof(char *) * (3));
	for_export[0] = ft_strjoin("toto", "tata");
	for_export[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	for_export[2] = NULL;
	printf("printf pwd %s\n", for_export[0]);
	export(for_export, envp);
	free_tab(for_export);
	return (0);
}
