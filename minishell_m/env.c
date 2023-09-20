/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:33:48 by akhaliss          #+#    #+#             */
/*   Updated: 2023/09/20 18:37:24 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **dup_env(char **env)
// {
//     int		i;
// 	char	**denv;

// 	i = -1;
// 	while(env[++i])
// 		;
// 	denv = malloc(sizeof(char *) * (i + 1));
// 	if(!denv)
// 		return(NULL);
// 	i = -1;
// 	while(env[++i])
// 	{
// 		denv[i] = ft_strdup(env[i]);
// 	}
// 	denv[i] = NULL;
// 	return(denv);
// }

void	split_env_var(char *env_str, t_envir *var)
{
	size_t	key_len;
	char	*equal_sign;

	equal_sign = ft_strchr(env_str, '=');
	if (!equal_sign) 
	{
		var->var = NULL;
		var->value = NULL;
		return ;
	}
	key_len = equal_sign - env_str;
	var->var = ft_substr(env_str, 0, key_len);
	var->value = ft_strdup(equal_sign + 1);
}

void	t_env(char **env)
{
	t_envir	*var;

	while (*env)
	{
		split_env_var(*env, var);
		env_tolist(&g_gb.env, node_envir(ft_strdup(*env),
				var->var, var->value));
		env++;
	}
}
