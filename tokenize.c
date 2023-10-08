/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:18:47 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 15:19:08 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	tokens(char c, char cc)
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

void	ft_word(t_token **line, char *str, t_envir **env, size_t *i)
{
	char	*s;

	s = ft_strdup("");
	if (!s)
		return ;
	while (str[*i] && !c_redi(str[*i]) && !v_spaces(str[*i]))
	{
		if (str[*i] == '\'')
			s = ft_strjoin(s, ft_single(str, i));
		else if (str[*i] == '"')
			s = ft_strjoin(s, ft_double(*env, str, i));
		else if (str[*i] == '$')
			s = ft_strjoin(s, expand_var(*env, str, i));
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
	token_tolist(line, node_token(s, WORD));
}

char	*ft_single(char *s, size_t *i)
{
	size_t	start;
	size_t	length;
	char	*ret;

	ret = NULL;
	if (s[*i] == '\'')
	{
		(*i)++;
		start = *i;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
		if (s[*i] == '\'')
		{
			length = *i - start;
			ret = ft_strncpy(s + start, length);
			(*i)++;
			return (ret);
		}
	}
	else
		(*i)++;
	return (NULL);
}

char	*ft_double(t_envir *env, char *s, size_t *i)
{
	char	*keep;

	keep = ft_strdup("");
	if (!keep)
		return (NULL);
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '"')
		{
			if (s[*i] == '$')
				keep = ft_strjoin(keep, expand_var(env, s, i));
			else
			{
				keep = ft_strjoin(keep, ft_substr(s, *i, 1));
				(*i)++;
			}
		}
		if (s[*i])
			(*i)++;
	}
	else
		(*i)++;
	return (keep);
}
