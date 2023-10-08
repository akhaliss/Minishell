/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:01:09 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 21:05:19 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_piping(int pipe_end[2], int	*exit_value)
{
	if (pipe(pipe_end) == -1)
	{
		perror("pipe");
		*exit_value = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	fork_failed(int *exit_value)
{
	perror("fork");
	*exit_value = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	dup_pipe_out(int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void ft_dup_in_out(int fd, int stand)
{
	dup2(fd, stand);
	close(fd);
}
