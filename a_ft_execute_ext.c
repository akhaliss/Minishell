/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ft_execute_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 21:00:30 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/08 21:06:13 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_exec *node, int pipe_end[], t_envir *env, int *exit_value)
{
	signal(SIGQUIT, SIG_DFL);
	if (node->out_fd != 1)
		ft_dup_in_out(node->out_fd, 1);
	if (node->in_fd != 0)
		ft_dup_in_out(node->in_fd, 0);
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
	{
		a_ftbuiltins(node, &env, exit_value);
		exit(0);
	}
	else
		command_exec(node, env, exit_value);
}

static void	dup_pipe_in(int *fd)
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

void	child_signal(int status, int *exit_value)
{
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

void	node_loop(t_exec *node, int *exit_value, t_envir **env, int pipe_end[])
{
	pid_t	pid;

	while (node)
	{
		if (node->next)
			ft_piping(pipe_end, exit_value);
		pid = fork();
		if (pid == -1)
			fork_failed(exit_value);
		else if (pid == 0)
			ft_child(node, pipe_end, *env, exit_value);
		if (node->next)
		{
			if (node->in_fd == 0)
			{
				node->in_fd = pipe_end[0];
				dup_pipe_in(pipe_end);
			}
			else
				close(pipe_end[0]);
		}
		node = node->next; 
	}
}

void	ft_execute(t_envir **env, t_exec	*node, int	*exit_value)
{
	int		status;
	t_exec	*head;
	int		pipe_end[2];
	int		backup;

	head = node;
	if (node && its_buildins(node) && !node->next)
	{
		a_ftbuiltins(node, env, exit_value);
		node = head;
		return ;
	}
	backup = dup(0);
	node_loop(node, exit_value, env, pipe_end);
	dup2(backup, 0);
	close(backup);
	while (waitpid(-1, &status, 0) != -1)
		;
	// node = head;///in case no garbage collectible
	child_signal(status, exit_value);
}
