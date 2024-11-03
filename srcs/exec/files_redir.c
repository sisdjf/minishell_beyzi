/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:16:41 by lybey             #+#    #+#             */
/*   Updated: 2024/11/04 00:55:32 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

void	file_error(t_stock *stock, char *str)
{
	if (access(stock->exec.path, F_OK) == 0)
	{
		fprintf(stderr, "%s: Permission denied\n", stock->exec.path);
	}
	else
	{
		fprintf(stderr, "%s: No such file or directory\n", stock->exec.path);
	}
	close_fds(stock);
}

void	close_fds(t_stock *stock)
{
	if (stock->exec.fd_tmp > 0)
		close(stock->exec.fd_tmp);
	if (stock->exec.fd_pipe[0] > 0)
		close(stock->exec.fd_pipe[0]);
	if (stock->exec.fd_pipe[1] > 0)
		close(stock->exec.fd_pipe[1]);
}


// int	ft_dup2_redir_files(int fd, t_token *tmp, t_token *tok, t_stock *stock)
// {
// 	if (fd == -1)
// 	{
// 		file_error(tok,stock, tmp->next->str);
// 		return (0);
// 	}
// 	if (tmp->type == REDIR_R || tmp->type == D_REDIR_R)
// 		dup2(fd, STDOUT_FILENO);
// 	else if (tmp->type == REDIR_L || tmp->type == HERDOC)
// 		dup2(fd, STDIN_FILENO);
// 	if (tmp->type != HERDOC)
// 		close(fd);
// 	return (1);
// }

// int	redir_files(t_token *tok, int i, t_stock *sock)
// {
// 	int		fd;
// 	t_token	*tmp;

// 	tmp = find_curr_tok_pipe(&tok, i);
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == WORD)
// 		{
// 			tmp = tmp->next;
// 			continue ;
// 		}
// 		if (tmp->type == REDIR_R)
// 			fd = open(tmp->next->name, O_CREAT | O_RDWR | O_TRUNC, 0666);
// 		else if (tmp->type == D_REDIR_R)
// 			fd = open(tmp->next->name, O_CREAT | O_RDWR | O_APPEND, 0666);
// 		else if (tmp->type == REDIR_L)
// 			fd = open(tmp->next->name, O_RDONLY);
// 		else if (tmp->type == HERDOC)
// 			fd = find_heredoc(stock, tmp);
// 		if (!ft_dup2_in_redir_files(fd, tmp, tok, stock))
// 			return (0);
// 		tmp = tmp->next;
// 	}
// 	close_heredocs(data,stock->nb_hd);
// 	return (1);
// }