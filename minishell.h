/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpollito <cpollito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 12:42:19 by cpollito          #+#    #+#             */
/*   Updated: 2022/09/09 12:45:09 by cpollito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <signal.h>

# define ERRSYNTAX "minishell: syntax error near unexpected token\n"
# define OK			0
# define ERROR		1
# define MALLOC_ERR	12
# define SYNTAX_ERR 258

typedef enum e_types
{
	SEP,
	WORD,
	FIELD,
	EXP_FIELD,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_HEREDOC,
	PIPE,
}				t_types;

typedef struct s_token
{
	int				len;
	char			*value;
	int				type;
	int				join_flag;
	struct s_token	*next;

}				t_token;

typedef struct s_dollar
{
	char	*new_value;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	size_t	len;
	int		between_dollar_len;
	int		dollar;
	int		i;
	int		number_flag;
	int		null_flag;

}			t_dollar;

typedef struct s_info	t_info;

typedef struct s_envp
{
	char			*name;
	char			*sep;
	char			*value;
	struct s_envp	*next;
}				t_envp;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;

}				t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;

}				t_cmd;

typedef struct s_info
{
	char		*reserved_words[7];
	char		**envp;
	t_envp		*envp_list;		
	int			envp_y;
	int			exit_status;
	char		*shell_name;
	t_token		*token_list;
	t_cmd		*cmd_list;
	int			cmd_name;
	int			args_amount;
	int			ret_val;
	int			token_len;
	t_dollar	*dol_info;
	int			num_cmd;
}			t_info;

//main.c
void	ft_init_data(t_info *data);
char	*ft_readline(char *prompt);
void	minishell(t_info *data, char *str);

//PARSER

//check_syntax_main.c
int		preparser(t_info *data, char *line);
void	ft_syntax_err(t_info *data);
int		syntax_error(t_info *data);
//check_syntax.c
int		check_eve_quotes(char *str);
char	*check_quotes(char *line);
char	*check_redirect_and_pipe(t_info *data, char *line);

//lexer_main.c
void	divide_into_tokens(char *str, t_info *data);
int		token_in_single_quotes(char *str, int i, t_info *data);
int		token_in_double_quotes(char *str, int i, t_info *data);
int		token_of_word_type(char *str, int i, t_info *data);
int		token_of_sep_type(char *str, int i, t_info *data);
//lexer_pipe_redir_tokens.c
int		token_of_pipe_redir_type(char *str, int i, t_info *data);
//lexer_list_utils.c
t_token	*ft_create_token_list(char *str, int start, t_info *data);
void	ft_token_list_add_back(t_token **token_list, t_token *new);

//parser_main.c
void	put_tokens_to_cmd(t_info *data);
t_token	*parser_main(t_info *data, t_cmd **cmd, t_token **tmp, t_token **tmp2);
t_token	*tokens_handler(t_info *data, t_cmd *cmd, t_token *tmp, t_token	*tmp2);
//parser_redir_handler.c
t_token	*redir_handler(t_cmd **cmd, t_token **tmp);
//parser_tokens_handler.c
void	find_joining_tokens(t_info *data, t_token	*tmp2);
//parser_create_cmd_args.c
t_token	*create_cmd_args(t_info *data, t_cmd *cmd, t_token *tmp);
//parser_dollar_handler_main.c
void	dollar_handler(t_token **tmp, t_dollar **dol_info, t_info *data);
//parser_dollar_handler_prt1.c
void	dollar_parser(t_token **tmp, t_dollar **dol_info, t_info *data);
//parser_dollar_handler_prt2.c
void	dollar_expansion(t_token **tmp, t_dollar **dol_info, t_info *data);
//parser_utils.c
void	cmd_push_back(t_cmd **head);
void	free_func(char **ptr);
int		ft_isdelim(char *s);
int		ms_isspace(int c);

//EXECUTOR

//parsing_env_into_list.c
void	ft_parse_env(char **env, t_envp **envp_list, t_info *data);
t_envp	*ft_put_env_into_list(char *env);
void	ft_envp_list_add_back(t_envp **envp_list, t_envp *new);
void	ft_create_envp_arr(t_info *data, char **env);
//parsing_env_into_arr.c
void	ft_create_envp_arr(t_info *data, char **env);

//shlvl.c
void	ft_check_shell_lvl(t_info *data);

//builtins
int		ft_echo(t_info *data);
int		ft_pwd(t_info *data);
int		ft_cd(t_info *data);
int		ft_env(t_info *data);
int		ft_exit(t_info *data);
int		ft_export(t_info *data);
void	ft_check_dup_export(t_envp **env, t_envp *new);
int		ft_unset(t_info *data, int i);

//executor.c
int		executor(t_info *data);
int		just_do_it(t_info *data);
int		check_builtin(t_info *data);
int		this_is_buitlin(t_info *data);

//just_do_it.c
void	ft_waitpid(t_info *data);
void	do_pipe_or_not(t_info *data, int fdin, int tmpout);
void	ft_fork(int tmpin, int tmpout, int fdin, t_info *data);
char	*ft_find_path(char **arr_cmd, t_info *data);
char	*ft_full_path(char **cmd_path, char	**arr_cmd);

//redirects.c
int		ft_redirects(t_info *data, int tmpin, int tmpout);
int		redir_in(t_redir *p, t_info *data);
int		redir_out(t_redir *p, t_info *data, int flag);
int		ft_redir_error(t_redir *p, t_info *data);
//heredoc.c
void	ft_heredoc(t_redir *p, int tmpin, int tmpout);
void	ft_write_in_pipe(int tmpin, int tmpout, int fdhere, t_redir *p);

//errors.c
void	fail_execve(t_info *data, char *path);
void	error_exit(int er_num, char *str);
void	norm_exit(t_info *data);

//utils.c
void	ft_reenv_arr(t_info *data);
char	**ft_recreate_arr_env(char **envp, t_envp *tmp, int *i);
void	free_node_envp(t_envp *tmp);
void	free_array_dup(char **arr);

//free_functions.c
void	free_cmd_list(t_info *data);
void	free_redir_list(t_redir *redir_list);
void	free_token_list(t_info *data);
void	free_data(t_info *data);

//signals.c
void	handler_ctl_c(int sig);
void	handler_fork(int sig_num);

#endif
