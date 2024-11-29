/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/11/29 03:05:15 by sizitout         ###   ########.fr       */
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

char	*get_cd_path(char **cmd, t_envp *envp)
{
	char	*path;

	if (!cmd[1])
	{
		path = find_env_var(envp);
		if (!path)
			return (NULL);
	}
	else
		path = cmd[1];
	return (path);
}

int	update_env_vars(char **for_export, t_envp **envp)
{
	char	*ro;

	ro = getcwd(NULL, 0);
	if (!ro)
		return (1);
	for_export[1] = ft_strjoin("PWD=", ro);
	export(for_export, envp);
	free(for_export[1]);
	return (0);
}

int	ft_cd(char **cmd, t_envp **envp)
{
	int		ret;
	char	*path;
	char	*for_export[3];
	char	*ro;

	for_export[0] = "";
	for_export[2] = NULL;
	if (!check_args_cd(cmd))
		return (0);
	path = get_cd_path(cmd, *envp);
	if (!path)
		return (0);
	ro = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret == -1)
		return (printf("cd : [%s]: No such file or directory\n", cmd[1]), 1);
	for_export[1] = ft_strjoin("OLDPWD=", ro);
	export(for_export, envp);
	free(ro);
	if (update_env_vars(for_export, envp) == 1)
		return (1);
	return (0);
}
