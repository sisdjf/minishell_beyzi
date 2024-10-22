/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:11:36 by lybey             #+#    #+#             */
/*   Updated: 2024/10/20 19:36:34 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pwd(char **cmd)
{
    char    *str;
    
    if(arg_len(cmd) > 1 && cmd[1][0] == '-') //verifier si y a autre chose que pwd
        return(printf("pwd : pas d'option\n")); //apres on utilisera putstr_fd au lieu de printf on a pas besoin pour le moment
    str = getcwd(NULL, 0); // getcwd pour recuperer le path
    if(!str)
    {
        printf("pwd: error retrieving current directory: getcwd:"); // message d'erreur sur bash
	    printf("cannot access parent directories: No such file or directory\n"); // message d'erreur sur bash
        
    }
    else
    {
        printf("%s\n", str);
	    free(str);
    }
    return(0);
}
