/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:29:09 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 12:01:00 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    free_token_list(t_token **tmp)
{
    t_token        *curr;
    t_token        *cmd;

    curr = *tmp;
    while (curr != NULL)
    {
        cmd = curr;
        curr = curr->next;
        if (cmd->word)
            free(cmd->word);
        free(cmd);
    }
    *tmp = NULL;
}
void ft_free(char **s)
{
    int i;
    if (!s)
        return ;
    i = 0;
    while(s[i])
        free(s[i++]);
    free(s);
    s = NULL;
    
}


void    free_exec_list(t_exec **mini)
{
    int            i;
    // char        **cmd;
    t_exec        *curr;
    t_exec        *tmp;

    i = 0;
    curr = *mini;
    while (curr != NULL)
    {
        tmp = curr;
        if (curr->in_fd != 0)
            close(curr->in_fd);
        if (curr->out_fd != 1)
            close(curr->out_fd);
        curr = curr->next;
            ft_free(tmp->cmd);
        free(tmp);
        // free(curr);
    }
    *mini = NULL;
}

void    free_env(t_envir **env)
{
    t_envir    *_env;

    _env = *env;
    while (_env)
    {
        free(_env->value);
        free(_env->var);
        _env = _env->next;
    }
    free(_env);
    *env = NULL;
}
