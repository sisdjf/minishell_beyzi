/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/09 02:32:37 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec(t_stock *stock)
{
	if (stock->exec.cmd_tab)
		free_tab(stock->exec.cmd_tab);
	if (stock->exec.env)
		free_tab(stock->exec.env);
	free(stock->exec.path);
}

static int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		stock->token = NULL;
		input = readline("minishell$ ");
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
		// to negatif
		ft_negatif(input);
		if (ft_token(stock, input) != 0)
		{
			return (free(input), 1);
		}
		input = ft_positif(input);
		// to positif
		ft_expand(stock, stock->token);
		// print_tab(stock->token);
		// si une seule cmd / builtin
		// lynda parsing ici (au lieu de tok to tab)
		stock_cmd_lst(stock);
		if (stock->exec.nb_cmd == 1 && check_builtins(stock->cmd->args) == 1)
		{
			printf("sur le builtins {%s}\n", stock->cmd->args[0]);
			builtins(stock->cmd->args, stock->envp);
			// free tt ce que tu dois free et continue la boucle;
			// continue ;
		}
		else
			ft_exec(stock);
		free_tokens(stock->token);
		// print_args(stock->cmd);
		free(input);
		free_cmd(&stock->cmd);
		free_exec(stock);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	static t_stock stock = {0};
	(void)argc;
	// (void)argv;
	stock_env_lst(env, &stock);
	ft_prompt(&stock, *argv);
	// printf("JE SUIS A LA FIN\n");
	ft_free_envp_list(&stock.envp);
	// free_tokens(stock.token);
	return (0);
}