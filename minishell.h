/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:17:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/27 01:12:39 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR_NL "bash: syntax error near unexpected token 'newline'\n"
# define ERROR_PIPE_MSG "bash: syntax error near unexpected token `|'\n"

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define DQUOTE '"'
# define SQUOTE '\''

extern int			g_globale;

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
	char			**cmd_tab;
	char			**env;
	int				fd_tmp;
	int				fd_pipe[2];
	int pid[1024]; // reverifie si c'est ok 1024 en brut ou pas
	int				nb_cmd;
	enum s_sign		type;
}					t_exec;

typedef struct s_redir
{
	char			*filename;
	t_sign			type;
	int				heredoc_fd[2];
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_heredoc
{
	char			*lim;
	int				fd_heredoc[2];
	int				index_cmd;
	int				totalsize;
	int				flag_heredoc;
}					t_heredoc;

typedef struct s_stock
{
	int				nb_hd;
	int				exit_status;
	int				fd_std[2];
	int				fd_out;
	char			*key;
	char			*value;
	char			*new_str;
	int				signal;
	t_token			*token;
	t_envp			*envp;
	t_exec			exec;
	t_cmd			*cmd;
	t_heredoc		*heredoc;
}					t_stock;

int					do_redir(t_cmd *cmd, int i, t_heredoc *here);
void				print_args(t_cmd *cmd);
void				stock_cmd_lst(t_stock *stock);
//QUOTES
int					ft_quotes(char *str);
char				*delete_quote(char *str);
//GUILLEMETS
// int					ft_double_quotes(char str);
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
char				*dd_quote(char *str, int *i);
void				ft_lstadd_back(t_token **token, t_token *new);
//TOKEN
int					skip_space(char *str, int *i);
int					ft_token(t_stock *stock, char *input);
void				chr_operator(char *input, t_token *token, int *i, int j);
void				free_tokens(t_token **token);
void				stock_redir_double_r(t_token *token, int *i);
void				stock_heredoc(t_token *token, int *i);
void				stock_redir_r(t_token *token);
void				stock_pipe(t_token *token);
void				stock_redir_l(t_token *token);
void				ft_negatif(char *input);
char				*ft_positif(char *input);

//UTILS
int					ft_strcmp(char *s1, char *s2);
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

//ENV
int					chr_equal(char *str);
t_envp				*ft_lstnew_envp(char *env_str);
void				ft_lstadd_back_envp(t_envp **token, t_envp *new);
void				stock_env_lst(char **env, t_stock *stock);
void				print_lst_envp(t_stock *stock);
//FREE
void				free_envp(t_envp **env);
void				ft_free_envp_list(t_envp **envp);
void				free_tab(char **tab);
void				free_heredoc(t_heredoc *heredoc);
//BUILTINS
int					check_n_option(char **cmd);
void				env(t_envp *envp);
int					echo(t_stock *stock, char **cmd);
int					print_echo(t_stock *stock, char **cmd, int start);
int					arg_len(char **array);
int					pwd(char **cmd);
int					builtins(t_stock *stock, char **cmd, t_envp **envp);
int					ft_cd(char **cmd, t_envp **envp);
char				*find_env_var(t_envp *envp);
int					check_args_cd(char **cmd);
int					ft_unset(char **cmd, t_envp *envp);
t_envp				*search_envp(t_envp *envp, char *key);
void				unset_loop(char **cmd, t_envp *envp);
int					add_to_env(char *key, char *value, t_envp **envp);
int					export(char **cmd, t_envp **envp);
int					ft_exit(t_stock *stock, char **cmd);
int					check_atoi_exit(t_stock *stock, char **cmd);
int					ft_atoi_exit(char *str);
int					nb_args_exit(char **cmd);
int					check_builtins(char **cmd);
char				**tok_to_tab(t_token *token);
// PARSE
int					nbr_malloc_word_cmd(t_token *token, int pipe);
int					stock_args_cmd(t_stock *stock, int pipe, t_cmd *new);
t_cmd				*ft_lstnew_cmd(t_stock *stock, int pipe);
void				ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new);
int					nb_cmd(t_token *token);
void				print_args(t_cmd *cmd);
void				stock_cmd_lst(t_stock *stock);
// int					stock_heredoc_cmd(t_token *token, int pipe, t_cmd *new);
int					stock_heredoc_cmd(t_stock *stock, int pipe, t_cmd *new);
int					stock_outfile_cmd(t_token *token, int pipe, t_cmd *new);
int					stock_infile_cmd(t_token *token, int pipe, t_cmd *new);
int					stock_appendfile_cmd(t_token *token, int pipe, t_cmd *new);
void				free_cmd(t_cmd **cmd);
//EXEC
// void				env(t_envp *envp);
char				*chr_path(t_stock *stock, t_envp *envp);
char				*path_to_cmd(t_stock *stock, t_exec *exec, t_envp *envp);
int					ft_exec(t_stock *stock);
void				free_split(char **split);
char				**tab_env(t_exec *exec, t_envp *envp);
int					init_struct_exec(t_stock *stock, int i);
char				**ft_find_tab(t_stock *stock, int i);
char				*ft_find_cmd_for_exec(t_stock *stock, int i);
void				pipe_redir(t_stock *stock, int i);
int					all_redir(t_stock *stock, int i);
void				free_exec(t_stock *stock);
int					redir_infile(t_stock *stock, int nb_cmd);
int					redir_outfile(t_stock *stock, int nb_cmd);
int					redir_appendfile(t_stock *stock, int nb_cmd);
void				close_fds(t_stock *stock);
//SIGNAUX
t_stock				*starton(void);
void				ft_gestion(int signum);
void				ft_gestion_heredoc(int signum);
void				disable_signals(void);
void				default_signals(void);
//HEREDOC
int					find_nb_hdoc(t_token *tok);
int					ft_error(int fd, char *str);
// int					find_nb_hdoc(t_stock *stock, t_heredoc *heredoc);
void				init_heredoc(t_stock *stock, t_heredoc *heredoc);
int					ft_heredoc(t_stock *stock);
void				exec_heredoc(t_stock *stock, int *i);
int					prompt_heredoc(t_stock *stock, char *lim, int pipe);
void				close_heredoc_child(t_stock *stock);

#endif

#define RESET "\033[0m"

#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

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
