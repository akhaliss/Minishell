/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:08:58 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 17:09:44 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_export(t_exec *node, t_envir **env)
{
	t_envir	*envp;

	envp = *env;
	while ((*env))
	{
		ft_putstr("declare -x ", node->out_fd);
		ft_putstr((*env)->var, node->out_fd);
		if ((*env)->value)
		{
			ft_putstr("=\"", node->out_fd);
			ft_putstr((*env)->value, node->out_fd);
			ft_putstr("\"", node->out_fd);
		}
		ft_putstr("\n", node->out_fd);
		(*env) = (*env)->next;
	}
	*env = envp;
}

static void	export_error(t_exec *node, int *exit_value)
{
	ft_putstr("minishell: export : '", 2);
	ft_putstr(node->cmd[1], 2);
	ft_putstr("': not a valid identifier\n", 2);
	*exit_value = 1;
}

static int	not_valid_char(char c)
{
	if ((c < '0' || c > '9') && (!ft_isalpha(c)) && c != '_' && c != '+')
		return (1);
	return (0);
}

static int	check_export_arg(t_exec *node, int i)
{
	int		j;

	if ((node->cmd[i][0] != '_' && (!ft_isalpha(node->cmd[i][0]))) 
		|| node->cmd[i][0] == '\"' || node->cmd[i][0] == '\'')
		return (1);
	else
	{
		j = 1;
		while (node->cmd[i] && (node->cmd[i][j] && node->cmd[i][j] != '='))
		{
			if (node->cmd[1][j] == '+' && node->cmd[1][j + 1] != '=')
				return (1);
			else if (not_valid_char(node->cmd[i][j]))
				return (1);
			j++;
		}
		if (node->cmd[i][j] == '=')
		{
			if (node->cmd[i][j - 1] == '+')
				return (2);
			return (3);
		}
	}
	return (0);
}

void	ft_export(t_exec *node, t_envir **env, int *exit_value)
{
	int		i;
	int		flag;

	i = 1;
	if (!node->cmd[1])
		just_export(node, env);
	else
	{
		while (node->cmd[i])
		{
			flag = check_export_arg(node, i);
			if (flag == 1)
				export_error(node, exit_value);
			else
				lets_export(flag, node, env, i);
			i++;
		}
	}
}
