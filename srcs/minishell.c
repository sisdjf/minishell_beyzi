/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/31 22:21:51 by lybey            ###   ########.fr       */
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
	free(tab);
}

void free_cmd(t_cmd *cmd)
{
	t_cmd *tmp;

	while(cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_tab(cmd->args);
		if (cmd->infile)
			free_tab(cmd->infile);
		if (cmd->outfile)
			free_tab(cmd->outfile);
		if (cmd->appendfile)
			free_tab(cmd->appendfile);
		if (cmd->heredoc)
			free_tab(cmd->heredoc);
		free(cmd);
		cmd = tmp;
	}
}

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
		stock_cmd_lst(stock);
		free_tokens(stock->token);		
		print_args(stock->cmd);
		free_cmd(stock->cmd);
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
	// free_tokens(stock.token);
	return (0);
}
