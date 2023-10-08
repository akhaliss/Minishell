/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:29:09 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 15:18:04 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *tmp)
{
	t_token		*curr;
	t_token		*cmd;

	curr = tmp;
	while (curr != NULL)
	{
		cmd = curr;
		curr = curr->next;
		// if (cmd->word)
			free(cmd->word);
		free(cmd);
	}
	// *tmp = NULL;
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i++]);
	}
	free(s);
	// s = NULL;
}

void	free_exec_list(t_exec *_free)
{
	t_exec		*curr;
	t_exec		*aux;
	int			i;

	curr = _free;
	while (curr != NULL)
	{
		aux = curr;
		if (curr->in_fd != 0)
			close(curr->in_fd);
		if (curr->out_fd != 1)
			close(curr->out_fd);
		curr = curr->next;
		// ft_free(aux->cmd);
		i = 0;
		while (aux->cmd[i])
		{
			free(aux->cmd[i++]);
		}
		free(aux->cmd);
		free(aux);
	}
}

void	free_env(t_envir **env)
{
	t_envir	*_env;

	_env = *env;
	while (_env)
	{
		free(_env->value);
		free(_env->var);
		_env = _env->next;
	}
	free(_env);
	// *env = NULL;
}
