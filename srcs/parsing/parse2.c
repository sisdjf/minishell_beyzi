/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:27:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/26 18:45:44 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_lstnew_redir(char *str, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = ft_strdup(str);
    new->type = type;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_redir(t_redir **redir, t_redir *new)
{
	t_redir	*last;

	last = *redir;
	if (*redir)
	{
		while (last && last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
	else
		*redir = new;
}

int malloc_redir(t_token *token, int i)
{
	t_token *tmp;
	int nb_malloc;
	int compteur;
	tmp = token;

	nb_malloc = 0;
	compteur = 0;
	while (compteur < i)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while(tmp)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			nb_malloc++;
		}
		tmp = tmp->next;
	}
	return (nb_malloc);
}

t_redir	*new_func_with_bilel(t_token *tok, int i)
{	
	int compteur;
	t_redir *head;
	t_token *tmp;
    t_redir *new_node;

	compteur = 0;
	head = NULL;
	tmp = tok;
	while(compteur < i)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
    		new_node = ft_lstnew_redir(tmp->next->name, tmp->type);
			if (new_node)
				ft_lstadd_back_redir(&head, new_node);
		}
		tmp = tmp->next;
	}
	return (head);
}

int	stock_args_cmd(t_stock *stock, int pipe, t_cmd *new)
{
	t_token	*tmp;
	int		nb_malloc;
	int		compteur;
	int		i;

	tmp = stock->token;
	compteur = 0;
	i = 0;
	nb_malloc = nbr_malloc_word_cmd(stock->token, pipe);
	new->args = ft_calloc(sizeof(char *), nb_malloc + 1);
	while (compteur < pipe)
	{
		if (tmp->type == PIPE)
			compteur++;
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			new->args[i++] = ft_strdup(tmp->name);
		if (tmp->type == D_REDIR_R || tmp->type == HERDOC
			|| tmp->type == REDIR_R || tmp->type == REDIR_L)
		{
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	new->args[i] = NULL;
	new->redir = new_func_with_bilel(stock->token, pipe);
	return (0);
}

// int	new_heredoc(t_cmd *cmd)
// {
// 	int		info;
// 	int		tmp_error;
// 	pid_t	pid;
// 	t_cmd *exec;

// 	exec = cmd;
// 	info = 0;
// 	if (exec->heredoc[i].lim)
// 		dectruction_heredoc(exec);
// 	exec->limiteur = ft_strdup(token->value);
// 	if (!exec->limiteur)
// 		return (-1);
// 	else
// 	{
// 		g_code_exit = FORK;
// 		pid = fork();
// 		if (pid == -1)
// 			return (perror("error fork"), -1);
// 		if (pid == 0)
// 			start_heredoc(exec, tmp_error);
// 		wait_heredoc(info, exec, tmp_error, pid);
// 	}
// 	return (0);
// }

// void	start_heredoc(t_exec *exec, int exit_code)
// {
// 	char	*line;
// 	char	***env;

// 	env = exec->g_parsing->env;
// 	g_code_exit = CHILD;
// 	line = NULL;
// 	exec->fd_infile = open("/tmp/here_doc_minishell",
// 			O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (exec->fd_infile == -1)
// 	{
// 		perror("open");
// 		return ;
// 	}
// 	g_code_exit = g_code_exit + exec->fd_infile;
// 	rl_catch_signals = 1;
// 	heredoc_loop(exec, exit_code, line, env);
// 	quit_heredoc(exec, line);
// }

int bon_heredoc(t_heredoc *here, char *file)
{
	int i = 0;
	while (i < here->totalsize)
	{
		fprintf(stderr, "compare [%s] | [%s]\n", file, here[i].lim);
		if (ft_strcmp(file, here[i].lim) == 0)
			return here[i].fd_heredoc[0];
		i++;
	}
	return -1;
}

int do_redir(t_cmd *cmd, int i, t_heredoc *here)
{
	t_redir *tmp;
	t_cmd *tmp_cmd;
	int go_to;
	int fd;

	go_to = 0;
	tmp_cmd = cmd;
	while(go_to < i)
    {
        tmp_cmd = tmp_cmd->next;
        go_to++;
    }
	tmp = tmp_cmd->redir;
	fprintf(stderr, "je suis {%s} avec {%p}", tmp_cmd->args[0], tmp);
	while(tmp)
	{
		if (tmp->type == REDIR_R)
			fd = open(tmp->filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
		else if (tmp->type == D_REDIR_R)
			fd = open(tmp->filename, O_CREAT | O_RDWR | O_APPEND, 0666);
		else if (tmp->type == REDIR_L)
			fd = open(tmp->filename, O_RDONLY);
		else if (tmp->type == HERDOC)
			fd = bon_heredoc(here, tmp->filename);
			// fd = tmp->heredoc_fd[0];
		if (tmp->type == REDIR_R || tmp->type == D_REDIR_R)
			dup2(fd, STDOUT_FILENO);
		else if (tmp->type == HERDOC || tmp->type == REDIR_L)
		{
			dup2(fd, STDIN_FILENO);
		}
		if (tmp->type != HERDOC)
			close(fd);
		tmp = tmp->next;
	}
	return (0);
}
