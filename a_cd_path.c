/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_cd_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:38:34 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/07 16:24:34 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_envir **env, char *home)
{
	t_envir	*envp;

	envp = *env;
	while ((*env) && ft_strcmp((*env)->var, "PWD"))
		(*env) = (*env)->next;
	if ((*env))
		(*env)->value = home;
	*env = envp;
}

void	update_oldpwd(t_envir **env, char *pwd)
{
	t_envir	*envp;

	envp = (*env);
	while ((*env) && ft_strcmp((*env)->var, "OLDPWD"))
		(*env) = (*env)->next;
	if ((*env))
		(*env)->value = ft_strdup(pwd);
	*env = envp;
}
