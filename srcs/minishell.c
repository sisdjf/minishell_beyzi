/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:20:22 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/24 03:13:44 by sizitout         ###   ########.fr       */
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
		dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_globale = 130;
	}
	else if (signum == SIGQUIT)
	{
		g_globale = 131;
		rl_replace_line("", 0);
		rl_redisplay();
		// free_exec(stock);
		// free_tokens(&stock->token);
		// ft_free_envp_list(&stock->envp);
		// free_cmd(&stock->cmd);
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

static int	ft_prompt(t_stock *stock, char *input)
{
	while (1)
	{
		stock->nb_hd = 0;
		stock->token = NULL;
		stock->cmd = NULL;
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
			ft_heredoc(stock);
			free_tokens(&stock->token);
		}
		if (stock->exec.nb_cmd == 1 && check_builtins(stock->cmd->args) == 1)
		{
			stock->fd_std[0] = dup(STDIN_FILENO);
			stock->fd_std[1] = dup(STDOUT_FILENO);
			// stock->heredoc->flag_heredoc = 1;
			init_struct_exec(stock, 0);
			all_redir(stock, 0);
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
		free_tokens(&stock->token);
		// print_args(stock->cmd);
		free(input);
		free_cmd(&stock->cmd);
		//free_exec(stock);
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
	signal(SIGINT, &ft_gestion);
	signal(SIGQUIT, SIG_IGN);
	// (void)argv;
	stock_env_lst(env, stock);
	ft_prompt(stock, *argv);
	ft_free_envp_list(&stock->envp);
	// free_tokens(stock.token);
	return (0);
}