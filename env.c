/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:33:48 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/09 14:30:24 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_en	*split_env(char *env_str, t_en *en)
{
	size_t	key_len;
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	key_len = equal_sign - env_str;
	en->var = ft_substr(env_str, 0, key_len);
	en->value = ft_strdup(equal_sign + 1);
	return (en);
}

t_envir	*t_env(char **env)
{
	int		i;
	t_envir	*head;
	t_en	*_env;
	t_envir	*tmp;

	i = 0;
	_env = malloc(sizeof(t_en));
	head = NULL;
	tmp = NULL;
	i = 0;
	while (env[i])
	{
		_env = split_env(*(env + i), _env);
		env_tolist(&tmp, node_envir(_env->var, _env->value));
		free(_env->var);
		free(_env->value);
		if (!head)
			head = tmp;
		i++;
	}
	free(_env);
	tmp = NULL;
	return (head);
}

int	_compar(char *line, char *en)
{
	if (!line || !en)
		return (0);
	if (line[0] == 0 && en[0] == 0)
		return (1);
	while (*line && *en)
	{
		if (*line == *en)
		{
			if (*(line + 1) == '\0' && *(en + 1) == '\0')
				return (1);
		}
		else if (*line != *en)
			return (0);
		line++;
		en++;
	}
	return (0);
}

char	*split_env_var(char *env_str, t_envir *env)
{
	env_str += 1;
	while (env)
	{
		if (_compar(env_str, env->var))
		{
			if (env->value)
				return (free(env_str), ft_strdup(env->value));
		}
		env = env->next;
	}
	return (free(env_str), ft_strdup(""));
}
