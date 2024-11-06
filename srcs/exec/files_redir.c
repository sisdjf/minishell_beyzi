/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:16:41 by lybey             #+#    #+#             */
/*   Updated: 2024/11/06 03:11:03 by lybey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"


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


void	pipe_redic(t_stock *stock, int i)
{
	if (i != 0)
	{
		dup2(stock->exec.fd_tmp, 0);
		close(stock->exec.fd_tmp);
	}
	if (i != stock->exec.nb_cmd - 1)
		dup2(stock->exec.fd_pipe[1], 1);
	close(stock->exec.fd_pipe[0]);
	close(stock->exec.fd_pipe[1]);	
	// if(stock->exec.nb_cmd == 1)
}

int	redir_infile(t_stock *stock, int nb_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	ft_printf("HERE\n = %d\n", nb_cmd);
	while (tmp_cmd && j < nb_cmd)
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
				if (access(tmp_cmd->infile[i], F_OK) == 0)
					ft_printf("%s: Permission denied\n", tmp_cmd->infile[i]);
				else
					ft_printf("%s: No such file or directory\n", tmp_cmd->infile[i]);
				return (0);
			}
			i++;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		ft_printf("Aucun fichier d'entrée défini pour la commande %d\n", nb_cmd);
	}
	ft_printf("HERE2\n");
	return (1);
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

int	redir_outfile(t_stock *stock, int nb_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	while (tmp_cmd && j < nb_cmd)
	{
		j++;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	ft_printf("ICIIIIIIIII\n");
	if (tmp_cmd && tmp_cmd->outfile)
	{
		ft_printf("ICIIIIIIIII\n");
		while (tmp_cmd->outfile[i])
		{
			ft_printf("j'ouvre le fichier : %s\n", tmp_cmd->outfile[i]);
			fd = open(tmp_cmd->outfile[i], O_CREAT | O_RDWR | O_TRUNC, 0666);
			ft_printf("je suis la = %d\n", fd);
			if(fd == -1)
			{
				if (access(tmp_cmd->outfile[i], F_OK) == 0)
					ft_printf("%s: Permission denied\n", tmp_cmd->outfile[i]);
				else
					ft_printf("%s: No such file or directory\n", tmp_cmd->outfile[i]);
				return (0);
			}
			i++;
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		ft_printf("Aucun fichier de sortie défini pour la commande %d\n", nb_cmd);
	}

	return (1);
}

int	redir_appendfile(t_stock *stock, int nb_cmd)
{
	int		fd;
	int		j;
	int		i;
	t_cmd	*tmp_cmd;
	
	j = 0;
	tmp_cmd = stock->cmd;
	while (tmp_cmd && j < nb_cmd)
	{
		j++;
		tmp_cmd = tmp_cmd->next;
	}
	i = 0;
	ft_printf("ICIIIIIIIII\n");
	if (tmp_cmd && tmp_cmd->appendfile)
	{
		ft_printf("ICIIIIIIIII\n");
		while (tmp_cmd->appendfile[i])
		{
			ft_printf("j'ouvre le fichier : %s\n", tmp_cmd->appendfile[i]);
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
	else
	{
		ft_printf("Aucun fichier d'entrée défini pour la commande %d\n", nb_cmd);
	}

	return (1);
}