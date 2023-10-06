 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:18:47 by akhaliss          #+#    #+#             */
/*   Updated: 2023/09/22 14:44:20 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type tokens(char c, char cc)
{
    if (c == '<' && cc == '<')
        return (HEREDOC);
    else if (c == '>' && cc == '>')
       return (APPEND);
    else if (c == '>')
        return (OUT);
    else if (c == '<')
        return (IN);
    else if (c == '|')
        return (PIPE);
    else if (!ft_strchr(" \v\f\t\r<|>", c))
    	return (WORD);
	return (0);
}

void	ft_heredoc(t_token **line, char *str, t_type tok, size_t *i)
{
	*i += 2;
	token_tolist(line, node_token("<<", tok));
	while (str[*i] && v_spaces(str[*i]))
		*i += 1;
	_delim(line, str, i);
}
void	ft_append(t_token **line, t_type tok, size_t *i)
{
	*i +=2;
	token_tolist(line, node_token(">>", tok));
}

void	ft_out(t_token **line, t_type tok, size_t *i)
{
	*i +=1;
	token_tolist(line, node_token(">", tok));
}

void	ft_in(t_token **line, t_type tok, size_t *i)
{

	*i +=1;
	token_tolist(line, node_token("<", tok));
}

void	ft_pipe(t_token **line, t_type tok, size_t *i)
{
	*i +=1;
	token_tolist(line, node_token("|", tok));
}

void	ft_word(t_token **line, char *str, t_envir **env, t_type tok, size_t *i)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		return ;
	while (str[*i] && !c_redi(str[*i]) && !v_spaces(str[*i]))
	{
		if (str[*i] == '\'')
		{
			s = ft_strjoin(s, ft_single(str, i));
		}
		else if (str[*i] == '"')
		{
			s = ft_strjoin(s, ft_double(*env, str, i));
		}
		else if (str[*i] == '$')
		{
			s = ft_strjoin(s, expand_var(*env, str, i));
		}
		else
		{
			while (str[*i] && str[*i] != '\'' && str[*i] != '"'
				&& str[*i] != '$' && !c_redi(str[*i]) && !v_spaces(str[*i]))
			{
				s = c_join(s, str[*i]);
				++*i;
			}
		}
	}
	token_tolist(line, node_token(s, tok));
	free(s);
}
