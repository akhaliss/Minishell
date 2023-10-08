/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 09:37:58 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/07 22:22:30 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int n)
{
	(void)n;
	if (waitpid(-1, 0, WNOHANG) == 0)// child processes still hanging
		return ;
	// rl_replace_line("", 0);
	printf ("\n");
	rl_on_new_line();
	rl_redisplay();
}

// void	handle_sigterm(void)
// {
	// printf ("exit\n");
// 	exit(0);
// }

void	ft_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
