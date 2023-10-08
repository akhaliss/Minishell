/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:34:59 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 19:52:25 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_error(t_exec *node, int i)
{
	ft_putstr("minishell: unset : '", 2);
	ft_putstr(node->cmd[i], 2);
	ft_putstr("': not a valid identifier\n", 2);
}

int	check_unset_arg(t_exec *node, int i)
{
	if (node->cmd[i][0] != '_' && (!ft_isalpha(node->cmd[i][0])) \
	&& node->cmd[i][0] != '\"' && node->cmd[i][0] != '\'')
	{
		unset_error(node, i);
		return (1);
	}
	return (0);
}

void	first_node(t_envir **env, t_envir **envp)
{
	(*env) = (*env)->next;
	(*env)->prev = NULL;
	(*envp) = (*env);
}

void	last_node(t_envir **env)
{
	(*env)->prev->next = NULL;
}

void	only_node(t_envir **env, t_envir **envp)
{
	(*env) = NULL;
	(*envp) = NULL;
}

void	middle_node(t_envir **env)
{
	(*env)->prev->next = (*env)->next;
	(*env)->next->prev = (*env)->prev;
}

void	ft_unset_cases(t_envir **env, t_envir	**envp)
{
	t_envir	*temp;

	temp = (*env);
	if (!(*env)->next && (*env)->prev)
		last_node((env));
	else if (!(*env)->prev && (*env)->next)
		first_node(env, envp);
	else if (!(*env)->next && !(*env)->prev)
		only_node(env, envp);
	else
		middle_node(env);
	free(temp);
}

void	ft_unset(t_exec *node, t_envir **env)
{
	int		i;
	t_envir	*envp;

	i = 1;
	envp = *env;
	if (!node->cmd[1])
		return ;
	while (node->cmd[i])
	{
		if (!check_unset_arg(node, i))
		{
			*env = envp;
			while (*env)
			{
				if (ft_strcmp((*env)->var, node->cmd[i]) == 0)
				{
					ft_unset_cases(env, &envp);
					break ;
				}
				(*env) = (*env)->next;
			}
		}
		i++;
	}
	*env = envp;
}
