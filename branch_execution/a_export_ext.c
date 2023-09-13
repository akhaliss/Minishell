/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:35:25 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/12 17:41:44 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aadd_node(char *str_var, char *str_val)
{
	t_env	*new;
	t_env	*envp;

	new = NULL;
	envp = g_gl.env;
	while (envp && envp->link)
		envp = envp->link;
	if (envp)
	{
		new = malloc (sizeof(t_env));
		if (!new)
			return ;
		new->var = str_var;
		new->value = str_val;
		new->link = NULL;
		new->prev = envp;
		envp->link = new;
	}
	else
		g_gl.env = new;
}

void	without_value(t_env *envp, char *str_var)
{
	int	flag;

	flag = 0;
	while (envp)
	{
		if (ft_strcmp(str_var, envp->var) == 0)
		{
			flag = 1;
			break ;
		}
		envp = envp->link;
	}
	if (flag == 0)
		aadd_node(str_var, NULL);
}

void	with_plus(t_env *envp, char *str_var, char *str_val)
{
	int	flag;

	flag = 0;
	str_var = ft_substr1(str_var, 0, ft_strlen(str_var) - 1);
	while (envp)
	{
		if (ft_strcmp(str_var, envp->var) == 0)
		{
			flag = 1;
			envp->value = my_strjoin(envp->value, str_val);
			break ;
		}
		envp = envp->link;
	}
	if (flag == 0)
		aadd_node(str_var, str_val);
}

void	without_plus(t_env *envp, char *str_var, char *str_val)
{
	int	flag;

	flag = 0;
	while (envp)
	{
		if (ft_strcmp(str_var, envp->var) == 0)
		{
			flag = 1;
			envp->value = str_val;
			break ;
		}
		envp = envp->link;
	}
	if (flag == 0)
		aadd_node(str_var, str_val);
}