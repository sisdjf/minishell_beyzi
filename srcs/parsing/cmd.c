// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cmd.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lybey <lybey@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/24 16:50:20 by lybey             #+#    #+#             */
// /*   Updated: 2024/10/25 01:26:17 by lybey            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../minishell.h"

// int	is_redirection(int type)
// {
// 	if (type == D_REDIR_R || type == HERDOC || type == REDIR_R
// 		|| type == REDIR_L)
// 		return (1);
// 	return (0);
// }

// void	stock_cmd(t_stock *stock, t_cmd *cmd)
// {
// 	t_token	*token;
// 	int		arg_index;

// 	token = stock->token;
// 	arg_index = 0;
// 	cmd->args = malloc(sizeof(char *) * MAX_ARGS);
// 	cmd->infile = NULL;
// 	cmd->outfile = NULL;
// 	cmd->appendfile = NULL;
// 	cmd->heredoc = NULL;
// 	while (token && token->type != PIPE)
// 	{
// 		if (is_redirection(token->type))
// 		{
// 			token = token->next;
// 			if (!token)
// 				break ;
// 			if (cmd->infile == NULL && token->type == REDIR_L)
// 				cmd->infile = ft_strdup(stock->value);
		
// 			else if (cmd->outfile == NULL && token->type == REDIR_R)
// 				cmd->outfile = ft_strdup(stock->value);
// 			else if (cmd->appendfile == NULL && token->type == D_REDIR_R)
// 				cmd->appendfile = ft_strdup(stock->value);
// 			else if (cmd->heredoc == NULL && token->type == HERDOC)
// 				cmd->heredoc = ft_strdup(stock->value);
// 		}
// 		else
// 		{
// 			cmd->args[arg_index] = ft_strdup(stock->token->name);
//             stock->token = stock->token->next;
// 			arg_index++;
// 		}
// 		token = token->next;
// 	}
// 	cmd->args[arg_index] = NULL;
// }
// t_cmd *parse_commands(t_stock *stock)
// {
//     t_cmd *cmd_list = NULL;
//     t_cmd *current_cmd = NULL;
//     t_token *current_token = stock->token;
//     t_cmd *new_cmd;
    
//     while (current_token)
//     {
//         new_cmd = malloc(sizeof(t_cmd));
//         stock_cmd(stock, new_cmd);

//         if (cmd_list == NULL)  // Si c'est la première commande
//         {
//             cmd_list = new_cmd;
//             current_cmd = cmd_list;
//         }
//         else  // Sinon, ajouter à la liste chainée
//         {
//             current_cmd->next = new_cmd;
//             current_cmd = new_cmd;
//         }

//         // Si on atteint un pipe, passer au token suivant
//         if (current_token && current_token->type == PIPE)
//         {
//             current_token = current_token->next;
//         }
//     }

//     return cmd_list;  // Retourner la liste chaînée des commandes
// }


// void ft_cmd(t_stock *stock)
// {
//     t_cmd *commands;
//     t_cmd *current;

//     // Boucle pour afficher ou exécuter chaque commande dans la liste chaînée
//     commands = parse_commands(stock);// Parser les commandes et leurs redirections
//     current = commands;
//     while (current)
//     {
//         printf("Commande avec arguments : \n");
//         for (int i = 0; current->args[i]; i++)
//         {
//             printf("Arg[%d] = %s\n", i, current->args[i]);
//         }
//         if (current->infile)
//             printf("Redirection d'entrée : %s\n", current->infile);
//         if (current->outfile)
//             printf("Redirection de sortie : %s\n", current->outfile);
//         if (current->appendfile)
//             printf("Redirection append : %s\n", current->appendfile);
//         if (current->heredoc)
//             printf("Heredoc : %s\n", current->heredoc);

//         current = current->next;  // Passer à la commande suivante
//     }
// }
