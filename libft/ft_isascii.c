/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:07:45 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/27 17:38:10 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*int main()
{
    int c = "100"; 
//or char c = 'a' il va te dire c un carct ascii (diff entre int et char)
    if (ft_isascii(c))
    write(1, "C'est un caractere ascii", 24);
else
    write(1, "C'est pas un caracte ascii", 27);
}*/
