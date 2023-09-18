#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"
# define INCORRECT 258

typedef enum s_type
{
    PIPE,
    HEREDOC,
    APPEND,
    OUT,
    IN,
    WORD
}	t_type;

typedef struct s_token
{
    char			*word;
    t_type			type;
    struct s_token	*prev;
    struct s_token	*next;
}	t_token;

typedef struct s_exec
{
    char		**cmd;
    int			in_fd;
    int			out_fd;
	struct s_exec	*next;
	struct s_exec	*prev;
}	t_exec;

typedef struct s_envir
{
    char    *env;
    char	*var;
    char	*value;
    struct s_envir *next;
}	t_envir;

typedef struct s_gb
{
    int exit_stat;
    t_envir *env;
}   t_gb;

t_gb    g_gb;


t_token		*tokenize_input(char *input);
t_token		*node_token(char* word, t_type type);
t_envir		*node_envir(char *env, char *key, char *value);
void		env_tolist(t_envir **head, t_envir *env);
void		token_tolist(t_token **head, t_token *token);
void		t_env(char **env);
int			next_quote(char *line, int i, int *nq, int q);
int			valid_quotes(char *line);
int			v_spaces(char l);
int			f_pipe(char *line);
void		stx_error(void);
int			line_syntax(char *line);
int			v_dollars(int l);
int			skip_(char *line);
#endif