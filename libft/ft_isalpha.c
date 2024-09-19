/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:28:30 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/23 16:56:37 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

/*int	main()
{
	char a = 'a';
	if (ft_isalpha(a))
	{
		write(1, "Character is Alphabet", 21);
	}
	else
	{
		write(1, "Character is Not Alphabet", 25);
	}
}*/
