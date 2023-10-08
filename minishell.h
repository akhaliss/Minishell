/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:44:52 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 21:05:08 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"
# define INCORRECT 258
# define WS " \v\t\f\r"

typedef enum s_type
{
	PIPE = 1,
	HEREDOC = 2,
	APPEND = 3,
	OUT = 4,
	IN = 5,
	WORD = 6,
	EXP_HERE = 7,
	NEXP_HERE = 8
}	t_type;


typedef struct s_token
{
	char			*word;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char		**cmd;
	int			inf;
	int			outf;
}	t_file;

typedef struct s_exec
{
	char			**cmd;
	int				in_fd;
	int				out_fd;
	struct s_exec	*next;
	struct s_exec	*prev;
}	t_exec;

typedef struct s_en
{
	char *var;
	char *value;
}	t_en;

typedef struct s_envir
{
	char			*var;
	char			*value;
	struct s_envir	*next;
	struct s_envir	*prev;
}	t_envir;

int	ctrl_c;

t_type		tokens(char c, char cc);
t_token		*node_token(char *word, t_type type);
t_envir		*node_envir(char *key, char *value);
t_exec		*node_cmd(char **cmd, int _if, int _of);
void		env_tolist(t_envir **head, t_envir *env);
void		token_tolist(t_token **head, t_token *token);
void		cmd_tolist(t_exec **head, t_exec *token);
t_envir*	t_env(char **env);
t_en		*split_env(char *env_str, t_en *en);
int			next_quote(char *line, int i, int *nq, int q);
int			valid_quotes(char **line);
int			v_spaces(char l);
void		stx_error(void);
int			line_syntax(char *line);
int			v_dollars(int l);
int			_redir(char **line);
int			_compar(char *line, char *en);
char		*split_env_var(char *env_str, t_envir *var);
char		*expand_var(t_envir *_env, char *s, size_t *i);
char		*c_join(char *s1, char c);
char		*ft_single(char *s, size_t *i);
char		*ft_double(t_envir *env, char *s, size_t *i);
void		parsing(t_token **line, char *str, t_envir **env, size_t *i);
void		parsed_tok(t_token **line, char *str, t_envir **env);
void		parse(char *line, t_envir **env, t_token **tmp, t_exec **mini);
void		ft_heredoc(t_token **line, char *str, t_type tok, size_t *i);
void		ft_append(t_token **line, t_type tok, size_t *i);
void		ft_out(t_token **line, t_type tok, size_t *i);
void		ft_in(t_token **line, t_type tok, size_t *i);
void		ft_pipe(t_token **line, t_type tok, size_t *i);
void		_delim(t_token **line, char *str, size_t *i);
void		ft_word(t_token **line, char *str, t_envir **env, t_type tok, size_t *i);
char		*delim_type(char *str, size_t *i, int *flg);
int			c_redi(char c);
int			_pipe(char **line);
void		to_exec(t_exec **line, t_token **parsed/*, t_envir **env*/);
t_file		*node_tmp(char **cmd);
int			cmd_size(t_token *line);
t_file		*_tmp(t_file *tmp);
t_token		*ft_files(t_token *line, t_file *tmp/*, t_envir **env*/);
char		*ft_dup(const char *s1);
void		m_files(t_file *fd, char *cmp, char *redir);
t_token		*prep_tmp(t_token *line, t_file *tmp/*, t_envir **env*/);
void		fill_arr(t_token *line, t_file *tmp);
void		free_token_list(t_token **tmp);
void		free_exec_list(t_exec **mini);
void		free_env(t_envir **env);
void		update_pwd(t_envir **env, char *home);
void		update_oldpwd(t_envir **env, char *pwd);
void		ft_cd(t_exec *node, t_envir	**env, int *exit_value);
void		ft_echo(t_exec *node);
void		ft_env(t_exec *node, t_envir *env, int *exit_value);
void		command_exec(t_exec *node, t_envir *env, int *exit_value);
void		a_ft_exit(t_exec *node);
void		without_value(t_envir **envp, char *str_var);
void		with_plus(t_envir **envp, char *str_var, char *str_val);
void		without_plus(t_envir **envp, char *str_var, char *str_val);
void		ft_export(t_exec *node, t_envir **env, int *exit_value);
void		ft_file_or_folder(t_exec *node, t_envir *env, int *exit_value);
void		ft_execute(t_envir **env, t_exec	*node, int	*exit_value);
char		**ft_env_tab(t_envir *env);
int			its_buildins(t_exec *node);
void		a_ftbuiltins(t_exec *node, t_envir **env, int *exit_value);
void		ft_pwd(t_exec *node, int *exit_value);
void		ft_unset(t_exec *node, t_envir **env);
void		handle_sigterm(void);
void		ft_signal(void);
void		lets_export(int flag, t_exec *node, t_envir **env, int i);



void	ft_piping(int pipe_end[2], int	*exit_value);
void	fork_failed(int *exit_value);
void	dup_pipe_out(int *fd);
void 	ft_dup_in_out(int fd, int stand);


#endif