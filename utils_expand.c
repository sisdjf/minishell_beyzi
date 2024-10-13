/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:51:42 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/12 18:27:08 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_joinstr(char *s1, char *s2)
{
    int     i;
    char    *res;

    if (!s1 && !s2)
        return (NULL);
    i = 0;
    res = malloc(ft_len_mini(s1) + ft_len_mini(s2) + 1);
    if (!res)
        return (NULL);
    while (i < ft_len_mini(s1))
    {
        res[i] = s1[i];
        i++;
    }
    while (i < ft_len_mini(s1) + ft_len_mini(s2))
    {
        res[i] = s2[i - ft_len_mini(s1)];
        i++;
    }
    res[i] = 0;
    free(s1);
    free(s2);
    return (res);
}
