/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ftbuiltins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:58:31 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 20:50:28 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	its_buildins(t_exec *node)
{
	if (!(ft_strcmp(node->cmd[0], "pwd")) \
	|| !(ft_strcmp(node->cmd[0], "cd")) || !(ft_strcmp(node->cmd[0], "echo")) \
	|| !(ft_strcmp(node->cmd[0], "env")) || \
	!(ft_strcmp(node->cmd[0], "export")) \
	|| !(ft_strcmp(node->cmd[0], "unset")) \
	|| !(ft_strcmp(node->cmd[0], "exit")))
		return (1);
	return (0);
}

void	a_ftbuiltins(t_exec *node, t_envir **env, int *exit_value)
{
	if (!(ft_strcmp(node->cmd[0], "pwd")))
		ft_pwd(node, exit_value);
	else if (!(ft_strcmp(node->cmd[0], "cd")))
		ft_cd(node, env, exit_value);
	else if (!(ft_strcmp(node->cmd[0], "echo")))
		ft_echo(node);
	else if (!(ft_strcmp(node->cmd[0], "env")))
		ft_env(node, *env, exit_value);
	else if (!(ft_strcmp(node->cmd[0], "export")))
		ft_export(node, env, exit_value);
	else if (!(ft_strcmp(node->cmd[0], "unset")))
		ft_unset(node, env);
	else if (!(ft_strcmp(node->cmd[0], "exit")))
		a_ft_exit(node);
}
