/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/10/03 22:48:57 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int builtins(char **cmd, t_envp *envp)
{
    (void)envp;
    if(!cmd)
        return(0);
    if(!strcmp(cmd[0], "echo"))
        return (echo(cmd), 1);
    else if(!strcmp(cmd[0], "cd"))
        return (ft_cd(cmd, envp), 1);
    else if(!strcmp(cmd[0], "pwd"))
        return (pwd(cmd), 1);
    // else if(!strcmp(cmd[0], "export"))
    //     return (export(cmd), 1);
     else if(!strcmp(cmd[0], "unset"))
        return (ft_unset(cmd, envp), 1);
    // else if(!strcmp(cmd[0], "env"))
    //     return (printf("env trouveeeeeeeeeeee\n"), 1);
    // else if(!strcmp(cmd[0], "exit"))
    //     return (printf("exit trouveeeeeeeeeeee\n"), 1);
    return (0);           
}