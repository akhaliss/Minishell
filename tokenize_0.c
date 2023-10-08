/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:01:13 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 11:21:08 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_token **line, char *str, t_type tok, size_t *i)
{
	*i += 2;
	token_tolist(line, node_token(ft_strdup("<<"), tok));
	while (str[*i] && v_spaces(str[*i]))
		*i += 1;
	_delim(line, str, i);
}

void	ft_append(t_token **line, t_type tok, size_t *i)
{
	*i += 2;
	token_tolist(line, node_token(ft_strdup(">>"), tok));
}

void	ft_out(t_token **line, t_type tok, size_t *i)
{
	*i += 1;
	token_tolist(line, node_token(ft_strdup(">"), tok));
}

void	ft_in(t_token **line, t_type tok, size_t *i)
{
	*i += 1;
	token_tolist(line, node_token(ft_strdup("<"), tok));
}

void	ft_pipe(t_token **line, t_type tok, size_t *i)
{
	*i += 1;
	token_tolist(line, node_token(ft_strdup("|"), tok));
}
