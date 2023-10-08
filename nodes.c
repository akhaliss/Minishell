/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:05:41 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 15:18:52 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*node_token(char *word, t_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->word = ft_strdup(word);
	token->type = type;
	free(word);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_envir	*node_envir(char *key, char *value)
{
	t_envir	*envir;

	envir = malloc(sizeof(t_envir));
	if (!envir)
		return (NULL);
	envir->var = ft_strdup(key);
	envir->value = ft_strdup(value);
	envir->next = NULL;
	return (envir);
}

t_exec	*node_cmd(char **cmd, int _if, int _of)
{
	(void)_if;
	(void)_of;
	(void)cmd;
	t_exec	*exec = NULL;

	// exec = malloc(sizeof(t_exec));
	// if (!exec)
	// 	return (NULL);
	// exec.cmd = cmd;
	// exec.in_fd = _if;
	// exec.out_fd = _of;
	// exec.next = NULL;
	// exec.prev = NULL;
	return (exec);
}

// t_file	node_tmp(void)
// {
// 	t_file tmp;
// 	tmp.inf = 0;
// 	tmp.outf = 1;
// 	return (tmp);
// }
