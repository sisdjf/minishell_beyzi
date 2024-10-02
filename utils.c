/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:52:29 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/02 00:41:23 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && (s1[i] == s2[i]))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_prompt(t_stock *stock)
{
	char *input;
	while (1)
	{
		input = readline("minishell ");
		if (!input)
			return (1);
		add_history(input);
		if (syntax_error(input))
		{
			free(input);
			return (1);
		}
		ft_token(stock, input);
		// chr_word(stock->token);
		printf("tt est ok\n");
		free(input);
	}
	return (0);
}
void	ft_path(void)
{
	char	*path;

	path = getenv("PATH");
	if (path != NULL)
		printf("path=%s\n", path);
}
