/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/21 15:59:49 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prompt(t_stock *stock, char *input)
{
	char	*str;
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
			printf("ICI 1\n");
			free(input);
			continue ;
		}
		free_tokens(stock->token);
		printf("ICI 2\n");
		stock->token = NULL;
		printf("ICI 3\n");
		if (ft_token(stock, input) != 0)
		{
			printf("ICI 4\n");
			return (free(input), 1);
		}
		printf("ICI 5\n");
		ft_expand(stock, stock->token);
		printf("ICI 6\n");
		str = delete_quote(input);
		printf("ICI 7\n");
		printf("str = %s\n", str);
		printf("ICI 8\n");
		// tok_to_tab(stock); revoir cette fonction avec lynda
		printf("ICI 9\n");
		// builtins(&input, stock->envp);
		builtins(stock->tab, stock->envp);
		printf("ICI 10\n");
		print_tab(stock->token);
		printf("ICI 11\n");
		printf("tt est ok\n");
		free(input);
		free(stock->tab);
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
