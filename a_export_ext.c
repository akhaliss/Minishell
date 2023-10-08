/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:35:25 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 17:10:21 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aadd_node(t_envir **env, char *str_var, char *str_val)
{
	t_envir	*new;
	t_envir	*old;

	old = *env;
	new = NULL;
	new = malloc (sizeof(t_envir));
	if (!new)
		return ;
	new->var = str_var;
	new->value = str_val;
	new->next = NULL;
	while ((*env) && (*env)->next)
		(*env) = (*env)->next;
	if ((*env))
	{
		new->prev = *env;
		(*env)->next = new;
		*env = old;
	}
	else
		*env = new;
}

void	without_value(t_envir **env, char *str_var)
{
	int		flag;
	t_envir	*envp;

	flag = 0;
	envp = *env;
	while (*env)
	{
		if (ft_strcmp(str_var, (*env)->var) == 0)
		{
			flag = 1;
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = envp;
	if (flag == 0)
		aadd_node(env, str_var, NULL);// free node
}

void	with_plus(t_envir **env, char *str_var, char *str_val)
{
	int		flag;
	t_envir	*envp;

	flag = 0;
	envp = *env;
	str_var = ft_substr1(str_var, 0, ft_strlen(str_var) - 1);
	while (*env)
	{
		if (ft_strcmp(str_var, (*env)->var) == 0)
		{
			flag = 1;
			(*env)->value = my_strjoin((*env)->value, str_val);
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = envp;
	if (flag == 0)
		aadd_node(env, str_var, str_val);
}

void	without_plus(t_envir **env, char *str_var, char *str_val)
{
	int		flag;
	t_envir	*envp;

	flag = 0;
	envp = *env;
	while (*env)
	{
		if (ft_strcmp(str_var, (*env)->var) == 0)
		{
			flag = 1;
			(*env)->value = str_val;
			break ;
		}
		(*env) = (*env)->next;
	}
	*env = envp;
	if (flag == 0)
		aadd_node(env, str_var, str_val);
}

void	lets_export(int flag, t_exec *node, t_envir **env, int i)
{
	char	*str_val;
	int		j;

	j = 0;
	while (node->cmd[i][j] && node->cmd[i][j] != '=')
		j++;
	str_val = ft_substr1(node->cmd[i], j + 1, ft_strlen(node->cmd[i]));
	if (flag == 0)
		without_value(env, ft_substr1(node->cmd[i], 0, j));
	else if (flag == 2)
		with_plus(env, ft_substr1(node->cmd[i], 0, j), str_val);
	else if (flag == 3)
		without_plus(env, ft_substr1(node->cmd[i], 0, j), str_val);
}
