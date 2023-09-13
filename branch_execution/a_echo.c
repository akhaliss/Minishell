/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */   
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 11:48:08 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/03 18:08:39 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_arg(char	*str, int fd)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(fd, &str[i++], 1);
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
	while(node->cmd[i] && node->cmd[i][j] == '-' && node->cmd[i][j + 1] == 'n')
	{
		j++;
		while (node->cmd[i] && node->cmd[i][j] == 'n')
			j++;
		if(node->cmd[i][j] == '\0')
		{
			i++;
			j = 0;
			flag = 1;
		}
		else
			break;
	}
	if(flag == 1)
	{
		while (node->cmd[i])
		{
			write_arg(node->cmd[i], node->out_fd);
			if (node->cmd[i + 1])
				write(node->out_fd, " ", 1);
			i++;
		}
	}
	else
	{
		while (node->cmd[i])
		{
			write_arg(node->cmd[i], node->out_fd);
			if (node->cmd[i + 1])
				write(node->out_fd, " ", 1);
			i++;
		}
		write(node->out_fd, "\n", 1);
	}
}