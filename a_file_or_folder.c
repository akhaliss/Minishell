/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_file_or_folder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:57:31 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 20:18:18 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_directory(t_exec *node, int *exit_value)
{
	ft_putstr("minishell: ", 2);
	ft_putstr(node->cmd[0], 2);
	ft_putstr(": is a directory\n", 2);
	*exit_value = 126;
	exit(126);
}

static void	is_file(t_exec *node, t_envir *env, int *exit_value)
{
	if (access(node->cmd[0], X_OK) != 0)
	{
		ft_putstr("minishell: ", 2);
		ft_putstr(node->cmd[0], 2);
		ft_putstr(": Permission denied\n", 2);
		*exit_value = 126;
		exit (126);
	}
	else
		execve(node->cmd[0], node->cmd, ft_env_tab(env));
}

void	ft_file_or_folder(t_exec *node, t_envir *env, int *exit_value)
{
	struct stat	file_info;

	if (stat(node->cmd[0], &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
			is_directory(node, exit_value);
		else if (S_ISREG(file_info.st_mode))
			is_file(node, env, exit_value);
		else
		{
			ft_putstr("minishell: ", 2);
			ft_putstr(node->cmd[0], 2);
			ft_putstr(": No such file or directory\n", 2);
			*exit_value = 127;
			exit (127);
		}
	}
	else
	{
		write(2, "minishell: ", 12);
		perror(node->cmd[0]);
		*exit_value = 127;
		exit (127);
	}
}
