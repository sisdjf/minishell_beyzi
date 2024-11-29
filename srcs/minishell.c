/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/29 23:57:24 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	one_builtins(t_stock *stock, char **input)
{
	stock->fd_std[0] = dup(STDIN_FILENO);
	stock->fd_std[1] = dup(STDOUT_FILENO);
	init_struct_exec(stock, 0);
	if (do_redir(stock->cmd, 0, stock->heredoc))
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

int	handle_heredoc(t_stock *stock)
{
	if (stock->nb_hd > 0)
	{
		if (ft_heredoc(stock) == 1)
		{
			free_tokens(&stock->token);
			return (1);
		}
		free_tokens(&stock->token);
	}
	return (0);
}

int	finish_prompt(t_stock *stock, char *input)
{
	input = ft_positif(input);
	ft_expand(stock, stock->token);
	stock_cmd_lst(stock);
	if (handle_heredoc(stock))
		return (1);
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

static int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		handle_signal();
		init_stock(stock);
		input = readline("minishell$ ");
		if (!input)
			return (1);
		if (!*input)
			continue ;
		add_history(input);
		if (handle_syntax_error_and_continue(stock, input))
			continue ;
		ft_negatif(input);
		if (ft_token(stock, input) != 0)
		{
			free(input);
			free(stock);
			return (1);
		}
		finish_prompt(stock, input);
		cleanup_execution(stock, &input);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_stock	*stock;

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
