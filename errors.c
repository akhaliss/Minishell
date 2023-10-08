/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:38:05 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/07 16:10:38 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stx_error(void)
{
	ft_putendl_fd("Minishell : syntax error", 2);
	// g_gb.exit_stat = 258;
}

void	voided(int ac, char **av)
{
	(void)av;
	(void)ac;
}

void	t_break(void)
{
	ft_putendl_fd("\nexit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
