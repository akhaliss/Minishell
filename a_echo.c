/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:05:57 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/06 15:13:27 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_arg(char	*str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write(fd, &str[i++], 1);
}

static void	write_argu(t_exec *node, int i)
{
	while (node->cmd[i])
	{
		write_arg(node->cmd[i], node->out_fd);
		if (node->cmd[i + 1])
			write(node->out_fd, " ", 1);
		i++;
	}
}

static void	check_flag(t_exec *node, int i, int flag)
{
	if (flag == 1)
		write_argu(node, i);
	else
	{
		write_argu(node, i);
		write(node->out_fd, "\n", 1);
	}
}

void	ft_echo(t_exec *node)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	j = 0;
	flag = 0;
	while (node->cmd[i] && node->cmd[i][j] == '-' && node->cmd[i][j + 1] == 'n')
	{
		j++;
		while (node->cmd[i] && node->cmd[i][j] == 'n')
			j++;
		if (node->cmd[i][j] == '\0')
		{
			i++;
			j = 0;
			flag = 1;
		}
		else
			break ;
	}
	check_flag(node, i, flag);
}
