/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_execv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:52:49 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/07 23:38:32 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path(t_envir	*env)
{
	char	**tab;
	t_envir	*envp;

	envp = env;
	tab = NULL;
	while (env && ft_strcmp(env->var, "PATH"))
	{
		env = env->next;
	}
	if (env)
		tab = aft_split(env->value, ':');
	env = envp;
	return (tab);
}

char	**ft_env_tab(t_envir *env)
{
	char	**tab;
	t_envir	*envp;
	int		size;
	int		i;

	i = 0;
	size = 0;
	envp = env;
	while (env)
	{
		size++;
		env = env->next;
	}
	env = envp;
	tab = malloc (sizeof(char *) * (size + 1));
	while (env)
	{
		if (!env->value)
			tab[i++] = ft_strdup(env->var);
		else
			tab[i++] = ft_strdup(ft_strjoin3(env->var, "=", env->value));
		env = env->next;
	}
	env = envp;
	tab[i] = NULL;
	return (tab);
}

static void	ft_exec_fail(t_exec *node, int *exit_value)
{
	ft_putstr("minishell: ", 2);
	ft_putstr(node->cmd[0], 2);
	ft_putstr(": command not found\n", 2);
	*exit_value = 127;
	exit (127);
}

static void	ft_joined_path(t_exec *node, t_envir *envp, char **path, int i)
{
	char	*str;

	while (path[i++])
	{
		str = ft_strjoin3(path[i], "/", node->cmd[0]);
		// node->cmd[0] = str;
		if (access(str, F_OK) == 0 && access(str, X_OK) == 0)
		{
			execve(str, node->cmd, ft_env_tab(envp));
			break ;
		}
	}
}

void	command_exec(t_exec *node, t_envir *env, int *exit_value)
{
	char	**path;
	t_envir	*envp;
	int		i;

	i = 0;
	envp = env;
	path = get_path(env);
	while (node->cmd[0][i])
	{
		if ((node->cmd[0][i] == '.' && node->cmd[0][i + 1] == '/') \
		|| node->cmd[0][i] == '/')
			ft_file_or_folder(node, env, exit_value);
		i++;
	}
	if (access(node->cmd[0], F_OK) == 0 && access(node->cmd[0], X_OK) == 0)
	{
		execve(node->cmd[0], node->cmd, ft_env_tab(env));
	}
	else
	{
		i = 0;
		ft_joined_path(node, env, path, i);
	}
	ft_exec_fail(node, exit_value);
}
