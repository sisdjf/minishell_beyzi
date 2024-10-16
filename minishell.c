/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/17 00:04:36 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
				if(!stock->tab[j])
					printf("error tab\n");
				// printf("---------- stock->tab[%d] = %s\n", j, stock->tab[j]);
				j++;
			}
		}
		tmp->token = tmp->token->next;
	}
	// printf("jjjjjjj = %d\n iiiii = %d\n", j, i);
	stock->tab[j] = NULL;
	free(stock->tab);
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
		tok_to_tab(stock);
		builtins(stock->tab, stock->envp);
		//cd_test(stock);
		printf("tt est ok\n");
		free(input);
		free(stock->tab);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	static t_stock	stock = {0};
	stock_env_lst(env, &stock);
	while (1)
	{
		ft_prompt(&stock);
	}
	return (0);
}