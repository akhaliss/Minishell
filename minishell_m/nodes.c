#include "minishell.h"

t_token *node_token(char *word, t_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (token)
    {
        token->word = ft_strdup(word);
        token->type = type;
        token->prev = NULL;
        token->next = NULL;
    }
    return (token);
}

t_envir *node_envir(char *env, char *key, char *value)
{
    t_envir *envir;

    envir = malloc(sizeof(t_envir));
    if (envir)
    {
        envir->env = env;
        envir->var = key;
        envir->value = value;
        envir->next = NULL;
    }
    return(envir);
}

t_exec	*node_cmd(char **cmd)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (exec)
	{
		exec->cmd = cmd;
		exec->in_fd = -1;
		exec->out_fd = -1;
	}
	return (exec);
}