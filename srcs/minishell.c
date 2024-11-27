/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/27 18:16:11 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			g_globale;

void	ft_gestion(int signum)
{
	t_stock	*stock;

	stock = starton();
	if (signum == SIGINT)
	{
		g_globale = 130;
		rl_done = 1;
	}
	else if (signum == SIGQUIT)
	{
		g_globale = 131;
		rl_done = 1;
		free_exec(stock);
		free_tokens(&stock->token);
		ft_free_envp_list(&stock->envp);
		free_cmd(&stock->cmd);
		free_heredoc(stock->heredoc);
		// g_globale = 131;
		// exit (131);
	}
}

void	free_exec(t_stock *stock)
{
	// if (stock->exec.cmd_tab)
	// 	free_tab(stock->exec.cmd_tab);
	if (stock->exec.env)
		free_tab(stock->exec.env);
	free(stock->exec.path);
}

int	event_hook(void)
{
	return (EXIT_SUCCESS);
}

static int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		signal(SIGINT, &ft_gestion);
		signal(SIGQUIT, SIG_IGN);
		g_globale = 0;
		stock->signal = 0;
		stock->nb_hd = 0;
		stock->token = NULL;
		stock->cmd = NULL;
		input = readline("minishell$ ");
		if (!input)
		{
			return (1);
		}
		if (!*input)
			continue ;
		add_history(input);
		if (syntax_error(input))
		{
			free(input);
			continue ;
		}
		ft_negatif(input);
		if (ft_token(stock, input) != 0)
		{
			free(input);
			free(stock);
			return (1);
		}
		input = ft_positif(input);
		ft_expand(stock, stock->token);
		// print_tab(stock->token);
		stock_cmd_lst(stock);
		if (stock->nb_hd > 0)
		{
			if (ft_heredoc(stock) == 1)
			{
				free_tokens(&stock->token);
				// free_heredoc(stock->heredoc);
				continue ;
			}
			free_tokens(&stock->token);
		}
		disable_signals();
		if (stock->exec.nb_cmd == 1 && check_builtins(stock->cmd->args) == 1)
		{
			stock->fd_std[0] = dup(STDIN_FILENO);
			stock->fd_std[1] = dup(STDOUT_FILENO);
			// stock->heredoc->flag_heredoc = 1;
			init_struct_exec(stock, 0);
			do_redir(stock->cmd, 0, stock->heredoc); // a changer
			builtins(stock, stock->cmd->args, &stock->envp);
			dup2(stock->fd_std[0], STDIN_FILENO);
			dup2(stock->fd_std[1], STDOUT_FILENO);
			close(stock->fd_std[0]);
			close(stock->fd_std[1]);
			free_exec(stock);
		}
		// REVENIR SUR LE DUP2
		else
			stock->exit_status = ft_exec(stock);
		if (stock->signal == 128 + SIGINT)
			ft_putstr_fd("\n", STDERR_FILENO);
		else if (stock->signal == 128 + SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		free_tokens(&stock->token);
		free(input);
		free_cmd(&stock->cmd);
		// free_exec(stock);
	}
	return (0);
}
t_stock	*starton(void)
{
	static t_stock	stock = {0};
	return (&stock);
}

int	main(int argc, char **argv, char **env)
{
	t_stock *stock;

	stock = starton();
	stock->exit_status = 0;
	(void)argc;
	// (void)argv;
	rl_event_hook = event_hook;
	stock_env_lst(env, stock);
	ft_prompt(stock, *argv);
	ft_free_envp_list(&stock->envp);
	free_cmd(&stock->cmd);
	// free_tokens(stock.token);
	return (0);
}