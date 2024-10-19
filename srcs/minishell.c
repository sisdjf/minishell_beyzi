/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/19 22:53:00 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (free(input), 1);
		ft_expand(stock, stock->token);
		// tok_to_tab(stock);
		// builtins(stock->tab, stock->envp);
		print_tab(stock->token);
		printf("tt est ok\n");
		free(input);
		// free(stock->tab);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	static t_stock	stock = {0};

	(void)argc;
	stock_env_lst(env, &stock);
	ft_prompt(&stock, *argv);
	ft_free_envp_list(stock.envp);
	free_tokens(stock.token);
	return (0);
}
