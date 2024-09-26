/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:58:40 by lybey             #+#    #+#             */
/*   Updated: 2024/09/27 00:24:00 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **cmd, char **env)
{
    
}

// Fonction pour trouver une variable dans l'environnement
int find_env_var(char **env, const char *var)
{
    int i = 0;
    int len = ft_strlen(var);
    
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return i;
        i++;
    }
    return -1;  // Variable non trouvée
}

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
