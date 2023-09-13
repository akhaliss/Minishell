/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:08:08 by abelkace          #+#    #+#             */
/*   Updated: 2023/09/08 11:10:33 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_exec *node)
{
	if (!node->cmd[1])
	{
		if (!getcwd(g_gl.pwd, PATH_MAX) && !access(g_gl.pwd, F_OK))
		{
			write(node->out_fd, "pwd failed\n", 11);
			return ;
		}
	}
	ft_putstr(g_gl.pwd, node->out_fd);
	write(node->out_fd, "\n", 1);
}

