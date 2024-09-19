/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:16:45 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/25 23:19:59 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	char a;
	if(ft_isdigit('8'))
	{
		write(1, "it s a variable", 15);
		}
		else
		{
		write(1, "it s a not variable", 19);
	}
}*/
