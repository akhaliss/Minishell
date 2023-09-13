/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:16:13 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/08 16:41:06 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd(t_env *env, char *home)
{
	t_env	*envp;

	envp = env;
	while (envp && ft_strcmp(envp->var, "PWD"))
		envp = envp->link;
	if (envp)
		envp->value = home;
}

static void	update_oldpwd(t_env *env, char *pwd)
{
	t_env	*envp;

	envp = env;
	while (envp && strcmp(envp->var, "OLDPWD"))
		envp = envp->link;
	if (envp)
		envp->value = pwd;
}

static void	just_cd(t_env *env)
{
	t_env	*envp;
	char	*pwd;
	char	*home;

	envp = env;
	while (envp && ft_strcmp(envp->var, "HOME"))
		envp = envp->link;
	if (envp)
		home = envp->value;
	envp = env;
	while (envp && ft_strcmp(envp->var, "PWD"))
		envp = envp->link;
	pwd = envp->value;
	if (chdir(home) == 0)
	{
		update_pwd(env, home);
		update_oldpwd(env, pwd);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 28);
}

static void	ft_fail(void)
{
	write(2, "cd: error retrieving current directory:\
	getcwd: cannot access parent directories: No such file or directory\n", 107);
}

void	ft_cd(t_exec *node)
{
	char	*temp;
	t_env	*envp;

	envp = g_gl.env;
	if (!node->cmd[1])
		just_cd(g_gl.env);
	else
	{
		while (envp && strcmp(envp->var, "PWD"))
			envp = envp->link;
		temp = envp->value;
		if (chdir(node->cmd[1]) == 0)
		{
			update_oldpwd(g_gl.env, temp);
			envp = g_gl.env;
			while (envp && strcmp(envp->var, "PWD"))
				envp = envp->link;
			if (!getcwd(g_gl.pwd, PATH_MAX) && node->cmd[1][0] == '.' )
				ft_fail();
			envp->value = g_gl.pwd;
		}
		else
			ft_chdir_fail(node);
	}
}
