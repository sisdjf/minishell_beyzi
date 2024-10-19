/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_lynda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:47:03 by lybey             #+#    #+#             */
/*   Updated: 2024/10/17 00:19:47 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char delete_quote(char *str)
{
    char *new;
    int i;
    int n;
    int c;

    new = malloc(sizeof(char ) * ft_strlen(str) + 1);
    i = 0;
    n = 0;
    while(str[i])
    {
        while(str[i] == '\'' || str[i] == '\"')
        {
            c = str[i++];
            while(str[i] != c)
                new[n++] = str[i++];
            i++;
        }
        if(str[i])
            new[n++] = str[i++];
    }
    new[i] = '\0';
    return(new);
}