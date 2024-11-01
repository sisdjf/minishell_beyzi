/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:17:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/09/04 21:52:24 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR_NL "bash: syntax error near unexpected token newline'\n"
# define ERROR_PIPE_MSG "bash: syntax error near unexpected token `|'\n"

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// typedef enum		sign;
// enum				s_sign
// {
// 	PIPE = '|',
// 	REDIR_R = '>',
// 	REDIR_L = '<',
// 	D_REDIR_R = '>>',
// 	HERDOC = '<<',
// 	// FICHIER = ,
// 	// ARGS = ,
// 	// CMD = ,
// 	// WORD,
// }					t_sign;

typedef enum				s_sign
{
	D_REDIR_R,
	HERDOC,
	REDIR_R,
	REDIR_L,
	PIPE,
	WORD,
}					t_sign;

typedef struct s_token
{
	char *name; // ">"
	struct s_token	*next;
	enum s_sign		type;
}					t_token;

typedef struct s_list
{
	int				sort;
	struct s_list	*next;
}					t_list;

typedef struct s_stock
{
	char			**tab;
	t_token			*token;
}					t_stock;

int					ft_prompt(t_stock *stock, char *input);
void				ft_path(void);
//GUILLEMETS
int					ft_quotes(char *str);
int					ft_double_quotes(char str);
int					syntax_error(char *input);
//GREATER
int					ft_greater_right(char *str);
int					s_loop_right(char *str, int *i, int nb_greater, int word);
int					ft_greater_left(char *str);
int					s_loop_left(char *str, int *i, int nb_greater, int word);
int					ft_double_greater_right(char *str);
int					d_loop_right(char *str, int *i, int nb_greater, int word);
int					ft_double_greater_left(char *str);
int					d_loop_left(char *str, int *i, int nb_greater, int word);
//PIPE
int					loop_pipe(char *str, int *i, int nb_pipe, int word);
int					ft_pipe(char *str);
//LST_UTILS
int					ft_lstsize(t_list *list);
t_list				*ft_lstnew(int value);
t_list				*lstend(t_list *list);
void				ft_lstadd_back(t_token **token, t_token *new);
//TOKEN
void				skip_space(char *str, int *i);
int					ft_token(t_stock *stock, char *input);
void				chr_operator(char *input, t_token *token, int *i);
//CHR_OPERATOR
char				*ft_greats_right(char *input);
char				*ft_greats_left(char *input);
char				*ft_double_greats_right(char *input);
char				*ft_double_greats_left(char *input);
char				*ft_chr_pipe(char *input);
//UTILS
int					ft_strcmp(char *s1, char *s2);

#endif

// #define RESET "\033[0m"

// #define BLACK "\033[30m"
// #define RED "\033[31m"
// #define GREEN "\033[32m"
// #define YELLOW "\033[33m"
// #define BLUE "\033[34m"
// #define MAGENTA "\033[35m"
// #define CYAN "\033[36m"
// #define WHITE "\033[37m"

// #define BBLACK "\033[40m"
// #define BRED "\033[41m"
// #define BGREEN "\033[42m"
// #define BYELLOW "\033[43m"
// #define BBLUE "\033[44m"
// #define BMAGENTA "\033[45m"
// #define BCYAN "\033[46m"
// #define BWHITE "\033[47m"

// #define CBLACK "\033[5;30m"
// #define CRED "\033[5;31m"
// #define CGREEN "\033[5;32m"
// #define CYELLOW "\033[5;33m"
// #define CBLUE "\033[5;34m"
// #define CMAGENTA "\033[5;35m"
// #define CCYAN "\033[5;36m"
// #define CWHITE "\033[5;37m"

// #define IBLACK "\033[3;30m"
// #define IRED "\033[3;31m"
// #define IGREEN "\033[3;32m"
// #define IYELLOW "\033[3;33m"
// #define IBLUE "\033[3;34m"
// #define IMAGENTA "\033[3;35m"
// #define ICYAN "\033[3;36m"
// #define IWHITE "\033[3;37m"
