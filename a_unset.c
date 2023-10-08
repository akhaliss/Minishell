/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:34:59 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 01:54:58 by abelkace         ###   ########.fr       */
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
void	test(t_envir **env)
{
	(*env)->prev->next = NULL;
}
void	test1(t_envir **env, t_envir **envp)
{
	(*env) = (*env)->next;
	(*env)->prev = NULL;
	(*envp) = (*env);
}

void	ft_unset(t_exec *node, t_envir **env)
{
	int		i;
	int		j;
	t_envir	*envp;
	t_envir	*temp;

	i = 1;
	j = 0;
	envp = *env;
	if (!node->cmd[1])
		return ;
	else
	{
		while (node->cmd[i])
		{
			if (!check_unset_arg(node, i))
			{
				*env = envp;
				while (*env)
				{
					if (ft_strcmp((*env)->var, node->cmd[i]) == 0)
					{
						temp = (*env);
						if (!(*env)->next && (*env)->prev)
							test((env));
						else if (!(*env)->prev && (*env)->next)
							test1(env, &envp);
						else
						{
							if (!(*env)->next && !(*env)->prev)
							{
								(*env) = NULL;
								envp = NULL;
							}
							else
							{
								(*env)->prev->next = (*env)->next;
								(*env)->next->prev = (*env)->prev;
							}
						}
						free(temp);
						break ;
					}
					(*env) = (*env)->next;
				}
			}
			i++;
		}
		*env = envp;
		return ;
	}
}