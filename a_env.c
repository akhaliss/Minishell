/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 03:15:14 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 16:36:05 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_exec *node, t_envir *env, int *exit_value)
{
	t_envir	*envp;

	envp = env;
	puts("__________________");
	if (node->cmd[1])
	{
		write (2, "env: ", 5);
		ft_putstr(node->cmd[1], 2);
		write(2, ": No such file or directory\n", 28);
		*exit_value = 127;
		return ;
	}
	while (env)
	{
		if (env->value)
		{
			ft_putstr(env->var, node->out_fd);
			write(node->out_fd, "=", 1);
			ft_putstr(env->value, node->out_fd);
			write(node->out_fd, "\n", 1);
		}
		env = env->next;
	}
	env = envp;
}
