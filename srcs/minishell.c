/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/06 03:19:27 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		stock->token = NULL;
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
		if (ft_token(stock, input) != 0)
		{
			return (free(input), 1);
		}
		ft_expand(stock, stock->token);
		print_tab(stock->token);
		// si une seule cmd / builtin
		// lynda parsing ici (au lieu de tok to tab)
		stock_cmd_lst(stock);
		free_tokens(stock->token);
		ft_exec(stock);
		free(input);
		free_cmd(stock->cmd);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	static t_stock	stock = {0};
	(void)argc;
	stock_env_lst(env, &stock);
	// while (stock.envp)
	// {
	// 	printf("%s\n", stock.envp->key);
	// 	stock.envp = stock.envp->next;
	// }
	// printf("ICI 13\n");
	ft_prompt(&stock, *argv);
	ft_free_envp_list(stock.envp);
	// free_tokens(stock.token);
	return (0);
}
