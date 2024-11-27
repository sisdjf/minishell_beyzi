// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   files_redir.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/04 00:16:41 by lybey             #+#    #+#             */
// /*   Updated: 2024/11/15 23:14:09 by sizitout         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../minishell.h"

int	ft_error(int fd, char *str)
{
	if (fd == -1)
	{
		if (access(str, F_OK) == 0)
			ft_printf("%s: Permission denied\n", str);
		else
			ft_printf("%s: No such file or directory\n", str);
		return (1);
	}
	return (0);
}
