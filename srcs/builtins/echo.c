/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:03:28 by lybey             #+#    #+#             */
/*   Updated: 2024/10/20 19:34:36 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int arg_len(char **array)
{
    int i;

    i = 0;
    if(!array)
        return (0);
    while(array[i])
        i++;
    return (i);
}

int print_echo(char **cmd, int start)
{
    int i;
    
    i = start;
    while(cmd[i])
    {
        printf("%s", cmd[i]);
        i++;
        if(cmd[i])
            printf(" ");
    }
    if(start == 1)
        printf("\n");
    return (0);
}

int    check_n_option(char **cmd)
{
    int i;
    int j;
    
    i = 1;
    while(cmd[i])
    {
        if(cmd[i][0] != '-')
        {
            j++;
            while(cmd[i][j])
            {
                if(cmd[i][j] != 'n' && cmd[i][j] != '\0')
                    return(i);
                j++;
            }
        }
        else
            return(i);
        j = 0;
        i++;
    }
    return(i);
}
int echo(char **cmd)
{
    int i;
    int nb_arg;

    i = 0;
    nb_arg = arg_len(cmd);
    if(nb_arg == 1)
        printf("\n");
    else if(i < nb_arg)
    {
        i = check_n_option(cmd);
        print_echo(cmd, i);
    }
    return (0);
}