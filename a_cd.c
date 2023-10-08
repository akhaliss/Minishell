/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 23:47:20 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 20:16:29 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_cd(t_envir **env, int *exit_value)
{
	t_envir	*envp;
	char	*pwd;
	char	*home;

	envp = *env;
	while ((*env) && ft_strcmp((*env)->var, "HOME"))
		(*env) = (*env)->next;
	if ((*env))
		home = (*env)->value;
	(*env) = envp;
	while ((*env) && ft_strcmp((*env)->var, "PWD"))
		(*env) = (*env)->next;
	pwd = (*env)->value;
	(*env) = envp;
	if (chdir(home) == 0)
	{
		update_pwd(env, home);
		update_oldpwd(env, pwd);
	}
	else
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		*exit_value = 1;
	}
}

static void	ft_fail(int *exit_value)
{
	write(2, "cd: error retrieving current directory:\
	getcwd: cannot access parent directories: No such file or directory\n", 108);
	*exit_value = 1;
}

static void	ft_chdir_fail(t_exec *node, int *exit_value)
{
	if (access(node->cmd[1], F_OK) == 0)
	{
		write(2, "cd: ", 4);
		perror(node->cmd[1]);
	}
	else
	{
		write(2, "cd: ", 4);
		perror(node->cmd[1]);
	}
	*exit_value = 1;
}

char	*get_pwd(t_envir **env)
{
	while ((*env) && ft_strcmp((*env)->var, "PWD"))
		(*env) = (*env)->next;
	return ((*env)->value);
}

void	ft_cd(t_exec *node, t_envir	**env, int *exit_value)
{
	t_envir	*envp;
	char	*temp;
	char	pwd[PATH_MAX];

	envp = *env;
	if (!node->cmd[1])
		just_cd(env, exit_value);
	else
	{
		temp = get_pwd(env);////
		(*env) = envp;
		if (chdir(node->cmd[1]) == 0)
		{
			update_oldpwd(env, temp);
			while ((*env) && ft_strcmp((*env)->var, "PWD"))
				(*env) = (*env)->next;
			if (getcwd(pwd, PATH_MAX) == NULL && node->cmd[1][0] == '.' )
				ft_fail(exit_value);
			(*env)->value = ft_strdup(pwd);
		}
		else
			ft_chdir_fail(node, exit_value);
	}
	*env = envp;
}
