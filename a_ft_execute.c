/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:01:09 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 16:30:24 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_piping(int pipe_end[2], int	*exit_value)
{
	if (pipe(pipe_end) == -1)
	{
		perror("pipe");
		*exit_value = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

static void	fork_failed(int *exit_value)
{
	perror("fork");
	*exit_value = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

static void	dup_pipe_out(int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

static void	ft_child(t_exec *node, int pipe_end[], t_envir *env, int *exit_value)
{
	signal(SIGQUIT, SIG_DFL);
	if (node->out_fd != 1)//redirection exist
	{
		dup2(node->out_fd, 1);
		close(node->out_fd);
	}
	if (node->in_fd != 0)
	{
		dup2(node->in_fd, 0);
		close(node->in_fd);
	}
	if (node->next)
	{
		if (node->out_fd == 1)
		{
			node->out_fd = pipe_end[1];
			dup_pipe_out(pipe_end);
		}
		else
			close(node->out_fd);
	}
	if (its_buildins(node))
		a_ftbuiltins(node, &env, exit_value);
	else
		command_exec(node, env, exit_value);
	exit(1);
}

static void	dup_pipe_in(int *fd)
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}
 
void	ft_execute(t_envir **env, t_exec	*node, int	*exit_value)
{
	int		status;
	t_exec	*head;
	int		pipe_end[2];
	pid_t	pid;
	int backup;

	head = node;
	if (node && its_buildins(node) && !node->next)
	{
		a_ftbuiltins(node, env, exit_value);
		node = head;
		return ;
	}
	backup = dup(0);
	while (node)
	{
		if (node->next)
			ft_piping(pipe_end, exit_value);
		pid = fork();
		if (pid == -1)
			fork_failed(exit_value);
		else if (pid == 0)
			ft_child(node, pipe_end, *env, exit_value);
		// close(pipe_end[1]);
		if (node->next)
		{
			if (node->in_fd == 0)
			{
				node->in_fd = pipe_end[0];
				dup_pipe_in(pipe_end);
			}
			else
			{
				close(pipe_end[0]);
				// close(node->next->in_fd);
			}
		}
		node = node->next; 
	}
	 dup2(backup, 0);
	 close(backup);
	while (waitpid(-1, &status, 0) != -1)
		;
	node = head;
	if (WIFEXITED(status))
		*exit_value = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3 || WTERMSIG(status) == 2)
		{
			*exit_value = WTERMSIG(status) + 128;
			if (WTERMSIG(status) == 2)
				printf ("\n");
			else if (WTERMSIG(status) == 3)
			{
				printf ("Quit: 3\n");
			}
		}
	}
}
