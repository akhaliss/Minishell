/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:34:59 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/13 16:19:44 by abelkace         ###   ########.fr       */
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

void	ft_unset(t_exec *node)
{
	int		i;
	int		j;
	t_env	*envp;
	t_env	*temp;

	i = 1;
	j = 0;
	if (!node->cmd[1])
		return ;
	else
	{
		while (node->cmd[i])
		{
			if (!check_unset_arg(node, i))
			{
				envp = g_gl.env;
				while (envp)
				{
					if (ft_strcmp(envp->var, node->cmd[i]))
						envp = envp->link;
					else
					{
						temp = envp;
						if (!envp->link)
						{
							envp->prev->link = NULL;
							envp = envp->prev;
							printf ("888888888888888envp->valrr%s\n", envp->var);
							free(temp);
							break ;
						}
						else if (!envp->prev && envp->link)
						{
							// envp->link->prev = NULL;
							g_gl.env = envp->link;
							free(temp);
							envp = g_gl.env;
							break ;
						}
						else
						{
							envp->prev->link = envp->link;
							envp->link->prev = envp->prev;
							envp = envp->prev;
							free(temp);
							break ;
						}
					}
				}
			}
			i++;
		}
		return ;
	}
}
