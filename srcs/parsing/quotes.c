/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:05:27 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/19 23:34:50 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *delete_quote(char *str)
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





// int	ft_quotes(char *str)
// {
// 	int	single_quote;
// 	int	double_quote;

// 	single_quote = 0;
// 	double_quote = 0;
// 	while (*str)
// 	{
// 		if (*str == '\'' && double_quote == 0)
// 		{
// 			single_quote = !single_quote;
// 		}
// 		else if (*str == '"' && single_quote == 0)
// 		{
// 			double_quote = !double_quote;
// 		}
// 		str++;
// 	}
// 	if (single_quote || double_quote)
// 	{
// 		printf("Error quote not close\n");
// 		return (1);
// 	}
// 	return (0);
// }
