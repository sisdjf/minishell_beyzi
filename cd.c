/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/10/01 23:29:57 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int check_args_cd(t_stock *stock, char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
        i++;
    if(i > 2)
    {
        printf("cd : too many arguments\n");
        return (0);
    }
    return(1);
}

char *find_env_var(t_envp *env)
{
    t_envp  *tmp;
    
    tmp = env;
    while(tmp)
    {
        if(!ft_strcmp(tmp->key, "HOME"))
            return((tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}





int ft_cd(char **cmd, t_envp env)
{
    int ret;
    char *path;

    if

    
}

















// Fonction pour trouver une variable dans l'environnement

// Fonction pour mettre à jour ou ajouter une variable d'environnement


int ft_cd(char **args, char ***env)
{
    char *dir;
    char cwd[1024];  // Buffer pour stocker le répertoire courant
    
    // Récupération du répertoire courant
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    // Si aucun argument n'est fourni, aller à HOME
    if (args[1] == NULL)
    {
        dir = getenv("HOME");
        if (dir == NULL) {
            printf("minishell: cd: HOME not set\n");
            return 1;
        }
    }
    return(0); 
}
