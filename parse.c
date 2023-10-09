/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:19:11 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/09 14:31:11 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*extract_var_name(char *s, size_t *i)
{
	size_t	var_name_len;
	char	*var_name;
	char	*var_start;

	var_name_len = 0;
	if (s[*i] == '$')
	{
		var_start = s + *i;
		var_name_len++;
		(*i)++;
		if (ft_isalpha(s[*i]) || s[*i] == '_')
		{
			while (s[*i] != '\0' && v_dollars(s[*i]))
			{
				var_name_len++;
				(*i)++;
			}
		}
	}
	var_name = malloc((sizeof(char) * (var_name_len + 1)));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, var_start, var_name_len + 1);
	return (var_name);
}

char	*expand_var_using_name(char *var_name, t_envir *_env)
{
	char	*expanded;

	// if (ft_strcmp(var_name, "?") == 0)
	//     return ft_itoa(g_gb.exit_st);
	expanded = split_env_var(var_name, _env);
	if (_env->var && _env->value)
		return (expanded);
	else
	{
		free(expanded);
		return (ft_strdup(var_name));
	}
}

char	*expand_var(t_envir *_env, char *s, size_t *i)
{
	char	*var_name;
	char	*expanded;

	// if (s[*i] == '$' && s[*i + 1] == '"')
	// {
	// 	return(ft_strdup("$")); 
	// }
	var_name = extract_var_name(s, i);
	if (var_name) 
	{
		expanded = expand_var_using_name(var_name, _env);
		return (expanded);
	} 
	return (ft_strdup(""));

}


	

char	*ft_expandvar(t_envir *_env, char *s, size_t *i)
{
	char	*s1;

	s1 = ft_strdup("");
	*i += 1;
	if (!s[*i])
		return (ft_strdup(s));
	while ((s[*i] != '\0') && v_dollars(s[*i]))
	{
		s1 = c_join(s1, s[*i]);
		*i += 1;
	}
	while (_env)
	{
		if (_compar(s1, _env->var))
		{
			if (_env->value)
				return (free(s1), ft_strdup(_env->value));
		}
		_env = _env->next;
	}
	return (free(s1), ft_strdup(""));
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
			*i += 1;
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
