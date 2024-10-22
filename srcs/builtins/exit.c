/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:34:19 by lybey             #+#    #+#             */
/*   Updated: 2024/10/20 19:35:33 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// char **cmd, cmd[0] == "exit"

// combien d'arguments apres?

// 0 args --> ft_printf("exit"), exit(0)

// 1 arg --> atoi 
// test exit 1 arg non-numeric --> fait bon message d'erreur, exit(2)
// exit(atoi(cmd[1]))

// 2 args ou plus, RETURN bon printf

// creer variable dans stock -> stock->exit_status

// rajoute free pour quitter proprement (free tout ce que minishell a
// alloue justqu'a ici)

int nb_args_exit(char **cmd)
{
    int i;
    i = 0;

    while(cmd[i])
    {
        i++;
    }
    return(i - 1);
}

int ft_exit(char **cmd)
{
    int i;
    
    i = nb_args_exit(cmd);
    printf("i = %d\n", i);
    if(i == 0)
        printf("exit\n");
    if(i == 1)
        check_atoi_exit(cmd);
    if(i == 2)
    {
        printf("exit :  too many arguments\n");
        return (1);
    }
    return (0);
}
