/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:14:29 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/07 16:08:49 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pipe(char **line)
{
	int	i;	

	if ((*line)[0] != '|')
		return (0);
	i = 1;
	while ((*line)[i] && v_spaces((*line)[i]))
		i++;
	if ((*line)[i] != '|' && (*line)[i])
		return (0);
	return (1);
}

int	next_quote(char *line, int i, int *nq, int q)
{
	int	j;

	j = i;
	*nq += 1;
	while (line[++j])
	{
		if (line[j] == q)
		{
			*nq += 1;
			break ;
		}
	}
	return (j - i);
}

int	valid_quotes(char **line)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	if ((*line)[i] == 34)
		i += next_quote(*line, i, &d, 34);
	else if ((*line)[i] == 39)
		i += next_quote(*line, i, &s, 39);
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	(*line) += i;
	return (1);
}

int	_redir(char **line)
{
	int		i;
	t_type	tok;

	if (**line != '>' && **line != '<')
		return (0);
	i = 0;
	tok = tokens((*line)[i], (*line)[i + 1]);
	if (tok == HEREDOC || tok == APPEND)
		*line += 2;
	else if (tok == IN || tok == OUT)
		*line += 1;
	if ((**line) == '\0' || (**line) == '|' || **line == '<' || **line == '>' )
		return (1);
	return (0);
}
