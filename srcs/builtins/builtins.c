/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:26:11 by lybey             #+#    #+#             */
/*   Updated: 2024/10/19 22:59:41 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int builtins(char **cmd, t_envp *envp)
{
    (void)envp;
    if(!cmd)
        return(0);
    if(!strcmp(cmd[0], "echo"))
        return (echo(cmd), 1);
    else if(!strcmp(cmd[0], "cd"))
        return (ft_cd(cmd, envp), 1);
    else if(!strcmp(cmd[0], "pwd"))
        return (pwd(cmd), 1);
    else if(!strcmp(cmd[0], "export"))
        return (export(cmd, envp), 1);
     else if(!strcmp(cmd[0], "unset"))
        return (ft_unset(cmd, envp), 1);
    else if(!strcmp(cmd[0], "env"))
        return (env(envp), 1);
    else if(!strcmp(cmd[0], "exit"))
        return (ft_exit(cmd), 1);
    return (0);      
}

// pas encore adapte pour les |
int get_nb_words(t_token *token)
{
	t_token	*tmp;
	int		word;
	
	tmp = token;
	word = 0;
	
	while(tmp)
	{
		if(tmp->name)
		{
			if (tmp->type == WORD)
			{
				word++;
			}
		}
		tmp = tmp->next;
	}
	return(word);
}
// pas encore adapte pour les | 
void tok_to_tab(t_stock *stock)
{
	int 	i;
	int		j;
	t_stock	*tmp;
	
	i = 0;
	j = 0;
	tmp = stock;
	i = get_nb_words(stock->token);
	// printf("iiiiiiiiiiiiiiii %d\n", i);
	tmp->tab = malloc(sizeof(char *) * (i + 1));
	if (!tmp->tab)
	{
		printf("Error tab malloc\n");
		return ;
	}
	while(tmp->token)
	{
		if(tmp->token->name)
		{
			// printf("--------- temp->name = %s\n", tmp->token->name);
			if (tmp->token->type == WORD)
			{
				tmp->tab[j] = ft_strdup(tmp->token->name);
				if(!tmp->tab[j])
					printf("error tab\n");
				// printf("---------- stock->tab[%d] = %s\n", j, stock->tab[j]);
				j++;
			}
		}
		tmp->token = tmp->token->next;
	}
	// printf("jjjjjjj = %d\n iiiii = %d\n", j, i);
	tmp->tab[j] = NULL;
	free(tmp->tab);
}