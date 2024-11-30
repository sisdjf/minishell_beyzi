/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 21:46:32 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	one_builtins(t_stock *stock, char **input)
{
	stock->fd_std[0] = dup(STDIN_FILENO);
	stock->fd_std[1] = dup(STDOUT_FILENO);
	init_struct_exec(stock, 0);
	if (do_redir(stock->cmd, 0))
	{
		free_exec(stock);
		free_tokens(&stock->token);
		free(input);
		free_cmd(&stock->cmd);
		close(stock->fd_std[0]);
		close(stock->fd_std[1]);
		return (1);
	}
	builtins(stock, stock->cmd->args, &stock->envp);
	dup2(stock->fd_std[0], STDIN_FILENO);
	dup2(stock->fd_std[1], STDOUT_FILENO);
	close(stock->fd_std[0]);
	close(stock->fd_std[1]);
	free_exec(stock);
	return (0);
}

int	finish_prompt(t_stock *stock, char *input)
{
	input = ft_positif(input);
	ft_expand(stock, stock->token);
	if (stock_cmd_lst(stock) == 1)
	{
		if (g_globale != 0)
		{
			stock->exit_status = g_globale;
			g_globale = 0;
		}
		return (1);
	}
	disable_signals();
	if (stock->exec.nb_cmd == 1 && check_builtins(stock->cmd->args) == 1)
	{
		if (one_builtins(stock, &input))
			return (1);
	}
	else
		stock->exit_status = ft_exec(stock);
	return (0);
}

int	ft_globale(t_stock *stock, char *input)
{
	if (g_globale != 0)
	{
		stock->exit_status = g_globale;
		g_globale = 0;
		free(input);
		return (1);
	}
	return (0);
}

static int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		handle_signal();
		init_stock(stock);
		input = readline("minishell$ ");
		if (ft_globale(stock, input))
			continue ;
		if (!input)
			return (ft_putendl_fd("exit", 2), 1);
		if (!*input)
			continue ;
		add_history(input);
		if (handle_syntax_error_and_continue(stock, input))
			continue ;
		ft_negatif(input);
		if (ft_token(stock, input) != 0)
			return (free(input), free(stock), (1));
		if (stock == NULL)
			continue ;
		finish_prompt(stock, input);
		cleanup_execution(stock, &input);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_stock	*stock;

	if (isatty(STDIN_FILENO) == 0)
	{
		return (1);
	}
	stock = starton();
	stock->exit_status = 0;
	(void)argc;
	rl_event_hook = event_hook;
	stock_env_lst(env, stock);
	ft_prompt(stock, *argv);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
	return (0);
}
