/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sizitout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:17:17 by sizitout          #+#    #+#             */
/*   Updated: 2024/11/30 22:05:13 by sizitout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define ERROR_NL "bash: syntax error near unexpected token 'newline'\n"
# define ERROR_PIPE_MSG "bash: syntax error near unexpected token `|'\n"
# define ERROR_SGR "bash: syntax error near unexpected token '>'\n"
# define ERROR_SGL "bash: syntax error near unexpected token '<'\n"
# define ERROR_DGR "bash: syntax error near unexpected token '>>'\n"
# define ERROR_DGL "bash: syntax error near unexpected token '<<'\n"

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
	int				pid[1024];
	int				nb_cmd;
	enum s_sign		type;
}					t_exec;

typedef struct s_redir
{
	char			*filename;
	t_sign			type;
	char			**heredoc_content;
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
	int				nb_pipe;
	int				nb_g;
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
}					t_stock;

extern int			g_globale;

int					do_redir(t_cmd *cmd, int i);
void				print_args(t_cmd *cmd);
//QUOTES
int					ft_quotes(char *str);
char				*delete_quote(char *str);
//GUILLEMETS
int					syntax_error(t_stock *stock, char *input);
//GREATER
int					ft_greater_right(t_stock *stock, char *str);
int					s_loop_right(t_stock *stock, char *str, int *i, int word);
int					ft_greater_left(t_stock *stock, char *str);
int					s_loop_left(t_stock *stock, char *str, int *i, int word);
int					ft_double_greater_right(t_stock *stock, char *str);
int					d_loop_right(t_stock *stock, char *str, int *i, int word);
int					ft_double_greater_left(t_stock *stock, char *str);
int					d_loop_left(t_stock *stock, char *str, int *i, int word);
int					special_technick(t_stock *stock, char *str);
//PIPE
int					loop_pipe(t_stock *stock, char *str, int *i, int word);
int					ft_pipe(t_stock *stock, char *str);
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
void				init_stock(t_stock *stock);
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
char				*double_quote(char *str, int *i, t_stock *data);

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
void				free_heredoc(t_heredoc *heredoc, t_stock *stock);
void				free_init_child(t_stock *stock);
void				free_redir(t_redir **redir);
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
char				*get_key_export(char *str);
int					printf_exit(t_stock *stock, char *str, int code);
// PARSE
int					nbr_malloc_word_cmd(t_token *token, int pipe);
int					stock_args_cmd(t_stock *stock, int pipe, t_cmd *new);
t_cmd				*ft_lstnew_cmd(t_stock *stock, int pipe);
void				ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *new);
int					nb_cmd(t_token *token);
void				print_args(t_cmd *cmd);
int					stock_cmd_lst(t_stock *stock);
int					stock_heredoc_cmd(t_stock *stock, int pipe, t_cmd *new);
int					stock_outfile_cmd(t_token *token, int pipe, t_cmd *new);
int					stock_infile_cmd(t_token *token, int pipe, t_cmd *new);
int					stock_appendfile_cmd(t_token *token, int pipe, t_cmd *new);
t_token				*index_token(t_token *token, int pipe);
void				free_cmd(t_cmd **cmd);
int					new_func_with_bilel(t_token *tok, int i, t_cmd *new);
t_redir				*ft_lstnew_redir(char *str, int type);
void				ft_lstadd_back_redir(t_redir **redir, t_redir *new);
int					bon_heredoc(t_heredoc *here, char *file);
//EXEC
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
void				analys_finish_process(t_stock *stock);
void				finish_exec(t_stock *stock, int i);
void				ft_child(t_stock *stock, int i);
void				free_all(t_stock *stock);
int					is_directory(const char *path);
void				half_child(t_stock *stock, int *i);
void				end_child(t_stock *stock);
void				free_child(t_stock *stock);
//SIGNAUX
t_stock				*starton(void);
void				ft_gestion(int signum);
void				ft_gestion_heredoc(int signum);
void				disable_signals(void);
void				default_signals(void);
int					event_hook(void);
//HEREDOC
int					find_nb_hdoc(t_token *tok);
int					ft_error(int fd, char *str);
// int					find_nb_hdoc(t_stock *stock, t_heredoc *heredoc);
void				init_heredoc(t_stock *stock, t_heredoc *heredoc);
int					ft_heredoc(t_stock *stock);
void				exec_heredoc(t_stock *stock, int *i);
int					prompt_heredoc1(t_redir *new);
void				close_heredoc_child(t_stock *stock);
int					ft_exit_fork(t_stock *stock, char **cmd);
int					builtins_fork(t_stock *stock, char **cmd, t_envp **envp);
//PROMPT
int					one_builtins(t_stock *stock, char **input);
void				cleanup_execution(t_stock *stock, char **input);
void				handle_signal(void);
int					handle_syntax_error_and_continue(t_stock *stock,
						char *input);

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
