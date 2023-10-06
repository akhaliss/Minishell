/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:29:09 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/06 10:55:50 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **tmp)
{
	t_token		*curr;
	t_token		*cmd;

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

void	free_exec_list(t_exec **mini)
{
	int			i;
	char		**cmd;
	t_exec		*curr;
	t_exec		*tmp;

	i = 0;
	curr = *mini;
	while (curr != NULL)
	{
		cmd = curr->cmd;
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
		close(curr->in_fd);
		close(curr->out_fd);
		tmp = curr->next;		
		free(curr);
		curr = tmp;
	}
	*mini = NULL;
}

void	free_env(t_envir **env)
{
	t_envir	*_env = *env;

	while(_env)
	{
		free(_env->value);
		free(_env->var);
		_env = _env->next;
	}
    free(_env);
	*env = NULL;
}