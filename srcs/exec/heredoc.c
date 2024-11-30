/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:07:48 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:04:21 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	add_string_char_2d(char ***tabb, char *str)
{
	char	**new;
	int		i;
	char	**buff;

	buff = *tabb;
	new = malloc(sizeof(char *) * (ft_strlen_2d(buff) + 1 + 1));
	i = 0;
	while (buff && buff[i])
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = str;
	new[++i] = NULL;
	free(buff);
	*tabb = new;
}

int	prompt_heredoc1(t_redir *new)
{
	char	*line;
	int		i;

	i = 1;
	while (1)
	{
		line = readline("> ");
		if (g_globale > 0)
			return (free_tab(new->heredoc_content), 1);
		if (!line)
		{
			ft_printf("warning: here-document at line\n",
				"%d delimited by end-of-file (wanted '%s')\n", i, new->filename);
			break ;
		}
		if (!ft_strcmp(line, new->filename))
			break ;
		add_string_char_2d(&new->heredoc_content, line);
		i++;
	}
	return (0);
}
