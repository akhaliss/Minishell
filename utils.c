/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:20:01 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/07 21:21:38 by akhaliss         ###   ########.fr       */
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

char	*c_join(char *s1, char c)
{
	char	*s2;

	s2 = malloc(sizeof(char) * (ft_strlen(s1) + 2));
	if (!s2)
		return (free(s1), NULL);
	ft_strcpy(s2, s1);
	s2[ft_strlen(s1)] = c;
	s2[ft_strlen(s1) + 1] = '\0';
	free(s1);
	return (s2);
}

int	line_syntax(char *line)
{
	if (*line == '|')
	{
		stx_error();
		return (0);
	}
	while (*line)
	{
		while (v_spaces(*line))
			line++; 
		if (!_pipe(&line) && !_redir(&line) && valid_quotes(&line))
			line++;
		else
			return (stx_error(), 0);
	}
	return (1);
}

int	c_redi(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
