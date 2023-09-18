#include "minishell.h"

void	env_tolist(t_envir **head, t_envir *env)
{
	t_envir *tmp;

	if (!head || !env)
		return ;
	tmp = *head;
	if (!*head)
		*head = env;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env;
	}
}

void token_tolist(t_token **head, t_token *token)
{
    t_token *tmp;

    if (!head || !token)
		return ;
	tmp = *head;
    if (*head == NULL)
    {
        *head = token;
    }
    else
    {
        while(tmp->next != NULL)
            tmp->next = tmp;
        tmp->next = token;
        token->prev = tmp;
    }
}
