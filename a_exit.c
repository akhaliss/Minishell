/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:18:59 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/06 15:15:24 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit_error(char *str)
{
	ft_putstr("minishell: exit: ", 2);
	ft_putstr(str, 2);
	ft_putstr(": numeric argument required\n", 2);
	exit(255);
}

void	a_ft_exit(t_exec *node)
{
	int	i;

	i = 0;
	if (!node->cmd[1])
		exit(0);
	else
	{
		while (node->cmd[1][i])
		{
			if (ft_isalpha(node->cmd[1][i++]))
			{
				printf("%s\n", "exit");
				ft_exit_error(node->cmd[1]);
			}
		}
		if (node->cmd[2])
			printf("%s\n%s\n", "exit", "minishell: exit: too many arguments");
		else
		{
			printf("%s\n", "exit");
			exit(ft_atoi(node->cmd[1]));
		}
	}
}
