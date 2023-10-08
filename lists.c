/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:38:50 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 15:06:52 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_tolist(t_envir **head, t_envir *env)
{
	t_envir	*tmp;

	if (!env)
		return ;
	tmp = *head;
	if (*head == NULL)
		*head = env;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = env;
		env->prev = tmp;
	}
}

void	token_tolist(t_token **head, t_token *token)
{
	t_token	*tmp;

	if (!head || !token)
		return ;
	if (*head == NULL)
	{
		*head = token;
		
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
		// token->prev = tmp;
	}

}

void	cmd_tolist(t_exec **head, t_exec *token)
{
	t_exec	*tmp;

	if (!head || !token)
		return ;
	if (*head == NULL)
		*head = token;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = token;
		// token->prev = tmp;
	}
}
