/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/25 19:02:19 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_prompt(t_stock *stock, char *input)
{
	char	**cmd_tab;

	cmd_tab = NULL;
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
		cmd_tab = tok_to_tab(stock->token);
		
		builtins(cmd_tab, stock->envp);
		// printf("ICI EXEC\n");
		stock->exec.cmd = cmd_tab[0];
		//boucle sur le nbr de cmd
			//pipe (1 fois)- fork(le nbr de cmd) -> faire les dup2 en fonction de la 1ere milieu ou derniere cmd
			ft_exec(&stock->exec, stock->envp, cmd_tab);
		// printf("ICI 10\n");
		// printf("ICI 11\n");
		printf("tt est ok\n");
		free(input);
		free_tokens(stock->token);
		// free_tab(stock->tab);
	}
	return (0);
}
// void	init_struct(t_stock *stock)
// {

// }
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
	//free_tab(stock.tab);
	ft_free_envp_list(stock.envp);
	// free_tokens(stock.token);
	return (0);
}
