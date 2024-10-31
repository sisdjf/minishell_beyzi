/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:17:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/10/31 21:13:02 by sizitout         ###   ########.fr       */
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

# define DQUOTE '"'
# define SQUOTE '\''

typedef enum s_sign
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
	char			*name;
	struct s_token	*next;
	enum s_sign		type;
}					t_token;

typedef struct s_envp
{
	char			*env_str;
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_list
{
	int				sort;
	struct s_list	*next;
}					t_list;

typedef struct s_exec
{
	char			**split_path;
	char			*path;
	char			*cmd;
	char			**env;
	int				fd_pipe[2];
	int				pid[1024]; // reverifie si c'est ok 1024 en brut ou pas
	enum s_sign		type;
}					t_exec;

typedef struct s_stock
{
	// char			**tab;
	char			*key;
	char			*value;
	char			*new_str;
	t_token			*token;
	t_envp			*envp;
	t_exec			exec;
}					t_stock;

int					ft_prompt(t_stock *stock, char *input);
//QUOTES
int					ft_quotes(char *str);
char				*delete_quote(char *str);
//GUILLEMETS
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
void				chr_operator(char *input, t_token *token, int *i, int j);
void				free_tokens(t_token *token);
void				stock_redir_double_r(t_token *token, int *i);
void				stock_heredoc(t_token *token, int *i);
void				stock_redir_r(t_token *token);
void				stock_pipe(t_token *token);
void				stock_redir_l(t_token *token);
//CHR_OPERATOR
char				*ft_greats_right(char *input);
char				*ft_greats_left(char *input);
char				*ft_double_greats_right(char *input);
char				*ft_double_greats_left(char *input);
char				*ft_chr_pipe(char *input);
//UTILS
int					ft_strcmp(char *s1, char *s2);
char				*ft_strcat(char *dest, char *src);
int					ft_len_mini(char *str);
void				print_tab(t_token *token);
//EXPAND
void				ft_expand(t_stock *stock, t_token *token);
char				*ft_joinstr(char *s1, char *s2);
char				*after_env_str(t_stock *stock, char *str, int *i);
char				*bool_expand(t_stock *stock, char *str);
char				*find_value(t_envp *env, char *key_start);
char				*all_dollar(char *str, int *i);
char				*ft_quotes_expand(t_stock *stock, char *str, int *i);
char				*bool_not_expand(char *str);
int					ft_strlen_check(char *str);
int					norm_quote(char *str, int i);
//
//ENV
int					chr_equal(char *str);
t_envp				*ft_lstnew_envp(char *env_str);
void				ft_lstadd_back_envp(t_envp **token, t_envp *new);
void				stock_env_lst(char **env, t_stock *stock);
void				print_lst_envp(t_stock *stock);
//FREE
void				free_envp(t_envp *env);
void				ft_free_envp_list(t_envp *envp);
void				free_tab(char **tab);
//BUILTINS
int					check_n_option(char **cmd);
void				env(t_envp *envp);
int					echo(char **cmd);
int					print_echo(char **cmd, int start);
int					arg_len(char **array);
int					pwd(char **cmd);
int					test_echo(t_stock *stock);
int					builtins(char **cmd, t_envp *envp);
int					cd_test(t_stock *stock);
int					ft_cd(char **cmd, t_envp *envp);
char				*find_env_var(t_envp *envp);
int					check_args_cd(char **cmd);
int					ft_unset(char **cmd, t_envp *envp);
t_envp				*search_envp(t_envp *envp, char *key);
void				unset_loop(char **cmd, t_envp *envp, int nb_cmd);
int					add_to_env(char *key, char *value, t_envp *envp);
int					export(char **cmd, t_envp *envp);
int					ft_exit(char **cmd);
int					check_atoi_exit(char **cmd);
int					ft_atoi_exit(char *str);
int					nb_args_exit(char **cmd);
// void				tok_to_tab(t_stock *stock);
char				**tok_to_tab(t_token *token);

//EXEC
// void				env(t_envp *envp);
char				*chr_path(t_envp *envp);
char				*path_to_cmd(t_exec *exec, t_envp *envp);
void				ft_exec(t_exec *exec, t_envp *envp, char **cmd);
void				free_split(char **split);
char				**tab_env(t_exec *exec, t_envp *envp);
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
