/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:08:58 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/11 16:44:34 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	just_export(t_exec *node)
{
	t_env	*envp;

	envp = g_gl.env;
	while (envp)
	{
		ft_putstr("declare -x ", node->out_fd);
		ft_putstr(envp->var, node->out_fd);
		if (envp->value)
		{
			ft_putstr(" =\"", node->out_fd);
			ft_putstr(envp->value, node->out_fd);
			ft_putstr("\"", node->out_fd);
		}
		ft_putstr("\n", node->out_fd);
		envp = envp->link;
	}
}

static void	export_error(t_exec *node)
{
	ft_putstr("minishell: export : '", 2);
	ft_putstr(node->cmd[1], 2);
	ft_putstr("': not a valid identifier\n", 2);
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
	t_env	*envp;

	envp = g_gl.env;
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

void	ft_export(t_exec *node)
{
	int		i;
	int		j;
	int		flag;
	char	*str_val;
	t_env	*envp;

	i = 1;
	if (!node->cmd[1])
		just_export(node);
	else
	{
		while (node->cmd[i])
		{
			envp = g_gl.env;
			flag = check_export_arg(node, i);
			if (flag == 1)
			{
				export_error(node);
				return ;
			}
			j = 0;
			while (node->cmd[i][j] && node->cmd[i][j] != '=')
				j++;
			str_val = ft_substr1(node->cmd[i], j + 1, ft_strlen(node->cmd[i]));
			if (flag == 0)
				without_value(envp, ft_substr1(node->cmd[i], 0, j));
			else if (flag == 2)
				with_plus(envp, ft_substr1(node->cmd[i], 0, j), str_val);
			else if (flag == 3)
				without_plus(envp, ft_substr1(node->cmd[i], 0, j), str_val);
			i++;
		}
	}
}
