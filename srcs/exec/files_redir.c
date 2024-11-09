/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:16:41 by lybey             #+#    #+#             */
/*   Updated: 2024/11/08 22:27:41 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"

int	ft_error(int fd, char *str)
{
	if(fd == -1)
	{
		if (access(str, F_OK) == 0)
			ft_printf("%s: Permission denied\n", str);
		else
			ft_printf("%s: No such file or directory\n", str);
		return (1);
	}
	return(0);
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

// int	ft_dup2_redir_files(int fd, t_stock *stock, t)
// {
// 	t_stock	*tmp;

// 	if (fd == -1)
// 	{
// 		file_error(stock, tmp->token->name);
// 		return (0);
// 	}
// 	if (tmp->token->type == REDIR_R || tmp->token->type == D_REDIR_R)
// 		dup2(fd, STDOUT_FILENO);
// 	else if (tmp->token->type == REDIR_L || tmp->token->type == HERDOC)
// 		dup2(fd, STDIN_FILENO);
// 	if (tmp->token->type != HERDOC)
// 		close(fd);
// 	return (1);
// }

int	redir_infile(t_stock *stock, int pos_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	while (tmp_cmd && j < pos_cmd)
	{
		j++;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	if (tmp_cmd && tmp_cmd->infile)
	{
		while (tmp_cmd->infile[i])
		{
			fd = open(tmp_cmd->infile[i], O_RDONLY);
			if(fd == -1)
			{
				ft_error(fd, tmp_cmd->infile[i]);
					return (1);
			}
			i++;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		return(1);
	return (0);
}

	// i = 0;
	// while(tmp_cmd->outfile[i])
	// {
	// 	fd = open(outfile[i])
	// 	i++;
	// }
		// // outfile trunc
		// 	fd = open(tmp->token->name, O_CREAT | O_RDWR | O_TRUNC);
		// // outfile append
		// 	fd = open(tmp->token->type, O_CREAT | O_RDWR | O_APPEND);

int	redir_outfile(t_stock *stock, int pos_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	while (tmp_cmd && j < pos_cmd)
	{
		j++;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	if (tmp_cmd && tmp_cmd->outfile)
	{
		while (tmp_cmd->outfile[i++])
		{
			fd = open(tmp_cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
			if(fd == -1)
			{
				ft_error(fd, tmp_cmd->outfile[i]);
					return (1);
			}
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);	
	}
	return (0);
}

int	redir_appendfile(t_stock *stock, int pos_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	while (tmp_cmd && j < pos_cmd)
	{
		j++;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	if (tmp_cmd && tmp_cmd->appendfile)
	{
		while (tmp_cmd->appendfile[i])
		{
			fd = open(tmp_cmd->appendfile[i], O_CREAT | O_RDWR | O_APPEND, 0666);
			if(fd == -1)
			{
				if (access(tmp_cmd->appendfile[i], F_OK) == 0)
					ft_printf("%s: Permission denied\n", tmp_cmd->appendfile[i]);
				else
					ft_printf("%s: No such file or directory\n", tmp_cmd->appendfile[i]);
				return (0);
			}
			i++;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}
