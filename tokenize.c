/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:18:47 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/09 17:37:53 by akhaliss         ###   ########.fr       */
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
	char	*tmp;

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
		{
			tmp = ft_expandvar(*env, str, i);
			if (!tmp)
				return ;
			s = ft_strjoin(s, tmp);
		}
		else
		{
			while (str[*i] && !ft_strchr("\'\">|< \t\v\r\f", str[*i]))
				s = c_join(s, str[(*i)++]);
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
			{
				if (s[*i] == '$' && !v_dollars(s[*i + 1]))
					keep = c_join(keep, s[*i]);
				keep = ft_strjoin(keep, expand_var(env, s, i));
			}
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
