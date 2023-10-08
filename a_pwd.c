/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:08:08 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 15:43:58 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_exec *node, int *exit_value)
{
	char	pwd[PATH_MAX];

	if (!node->cmd[1])
	{
		if (!getcwd(pwd, PATH_MAX) && !access(pwd, F_OK))
		{
			write(node->out_fd, "pwd failed\n", 11);
			*exit_value = 1;
			return ;
		}
	}
	ft_putstr(pwd, node->out_fd);
	write(node->out_fd, "\n", 1);
}
