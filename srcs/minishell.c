/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/23 22:11:30 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
}

int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		input = readline("minishell ");
		if (!input)
			return (1);
		if (!*input)
			continue ;
		add_history(input);
		if (syntax_error(input))
		{
			free(input);
			continue ;
		}
		free_tokens(stock->token);
		stock->token = NULL;
		if (ft_token(stock, input) != 0)
		{
			return (free(input), 1);
		}
		ft_expand(stock, stock->token);
		tok_to_tab(stock);
		// builtins(&input, stock->envp);
		builtins(stock->tab, stock->envp);
		printf("ICI EXEC\n");
		ft_exec(&stock->exec, stock->envp);
		printf("ICI 10\n");
		print_tab(stock->token);
		printf("ICI 11\n");
		printf("tt est ok\n");
		free(input);
		free_tab(stock->tab);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	static t_stock	stock = {0};
	(void)argc;
	printf("ICI le debut du main\n");
	stock_env_lst(env, &stock);
	// printf("ICI 13\n");
	ft_prompt(&stock, *argv);
	// ft_exec(stock.exec);
	// printf("Exec -> %s\n", stock.exec->path);
	// printf("ICI 14\n");
	ft_free_envp_list(stock.envp);
	free_tokens(stock.token);
	return (0);
}
