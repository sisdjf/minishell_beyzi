/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:19:33 by lybey             #+#    #+#             */
/*   Updated: 2024/11/08 21:13:06 by lybey            ###   ########.fr       */
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
    write(1, str, ft_strlen(str));
    (*len) += ft_strlen(str);
    return (i);
}