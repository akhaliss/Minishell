/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:20:01 by akhaliss          #+#    #+#             */
/*   Updated: 2023/09/20 20:21:08 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	v_spaces(char l)
{
	return (l == ' ' || l == '\v' || l == '\f'
		|| l == '\t' || l == '\r');
}

int	v_dollars(int l)
{
	return (ft_isalnum(l) || l == '_');
}

int	skip_(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && v_spaces(line[i]) && line[i] != '$')
		i++;
	if (line[i] == '$')
		return (i);
	return (0);
}
