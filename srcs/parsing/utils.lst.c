/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:10:31 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/12 20:03:43 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_list	*ft_lstnew(int value)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	new->sort = value;
	new->next = NULL;
	return (new);
}

t_list	*lstend(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (!list)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(t_token **token, t_token *new)
{
	t_token	*last;

	last = *token;
	if (*token)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*token = new;
}
