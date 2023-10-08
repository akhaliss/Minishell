/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:19:11 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/05 20:26:42 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_envir *_env, char *s, size_t *i)
{
	size_t		var_name_len;
	char		*expanded;
	char		*var_start;
	char		*var_name = NULL;

	var_name_len = 0;
	if (s[*i] == '$')
	{
		(*i)++;
		var_start = s + *i;
		if (ft_isalpha(s[*i]) || s[*i] == '_')
		{
			while (s[*i] != '\0' && v_dollars(s[*i]))
			{
				var_name_len++;
				(*i)++;
			}
		}
		var_name = malloc((sizeof(char) * (var_name_len + 1)));
		if (!var_name)
			return (NULL);
		ft_strlcpy(var_name, var_start, var_name_len + 1);
		// if (ft_strcmp(var_name, "?") == 0)
		//     return (ft_itoa(g_gb.exit_st));
		expanded = split_env_var(var_name, _env);
		// printf("EXP_VAR : %s\n", expanded);
		if (_env->var && _env->value)
			return (expanded);
		else
			return (free(var_name), free(expanded), ft_strdup(""));
	}
	return (free(var_name), ft_strdup(""));
}

char	*ft_single(char *s, size_t *i)
{
	size_t	start;
	size_t	length;
	char	*ret = NULL;

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
	while (s[*i] && !v_spaces(s[*i]) && !c_redi(s[*i]))
	{
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
		{
			keep = ft_strjoin(keep, ft_substr(s, *i, 1));
			(*i)++;
		}
	}
	return (keep);
}

int	c_redi(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	*delim_type(char *str, size_t *i, int *flg)
{
	char	*s;
	char	c;

	s = ft_strdup("");
	if (!s)
		return (NULL);
	while (str[*i] && !v_spaces(str[*i]) && !c_redi(str[*i]))
	{
		if (str[*i] == '$' && (str[*i + 1] == 39 || str[*i + 1] == 34))
			*i +=1;
		c = str[*i];
		if (str[*i] == 39 || str[*i] == 34)
		{
			*i += 1;
			while (str[*i] && str[*i] != c)
				s = c_join(s, str[(*i)++]);
		}
		else
		{
				s = c_join(s, str[(*i)++]);
			*flg = 1;
		}
	}
	return (s);
}

void	_delim(t_token **line, char *str, size_t *i)
{
	int		flg;
	char	*s;

	flg = 0;
	s = delim_type(str, i, &flg);
	if (flg == 0)
		token_tolist(line, node_token(ft_strdup(s), NEXP_HERE));
	else
		token_tolist(line, node_token(ft_strdup(s), EXP_HERE));
}

void	parsing(t_token **line, char *str, t_envir **env, size_t *i)
{
	t_type token;

	token = tokens(str[*i] , str[*i + 1]);
	if (token == HEREDOC)
		ft_heredoc(line, str, token, i);
	else if (token == APPEND)
		ft_append(line, token, i);
	else if (token == OUT)
		ft_out(line, token, i);
	else if (token == IN)
		ft_in(line, token, i);
	else if (token == PIPE)
		ft_pipe(line, token, i);
	else if (token == WORD)
		ft_word(line, str, env, token, i);
}

void	parsed_tok(t_token **line, char *str, t_envir **env)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] && v_spaces(str[i]))
			i++;
		parsing(line, str, env, &i);
	}
}
