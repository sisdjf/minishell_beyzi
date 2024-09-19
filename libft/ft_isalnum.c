/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:00:44 by sizitout          #+#    #+#             */
/*   Updated: 2023/05/27 17:37:49 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/*int	main()
{
	char a;
	a = "100"; //ou a = avec un apostrophe
	if (ft_isalnum(a))
	{
		printf("%s", "alpha-numerique", ft_isalnum(a));

	}
	else
	{
		printf("%s", "pas alpha numerique", ft_isalnum(a));
	}
}*/
