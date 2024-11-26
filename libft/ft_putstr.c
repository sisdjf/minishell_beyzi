/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:19:33 by lybey             #+#    #+#             */
/*   Updated: 2024/11/26 17:51:41 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

int    ft_putstr(char *str, int *len)
{
    int    i;

    i = 0;
    if (!str)
    {
        write(2, "(null)", 6);
        (*len) = *len + 6;
        return (0);
    }
    write(2, str, ft_strlen(str));
    (*len) += ft_strlen(str);
    return (i);
}