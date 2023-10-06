/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:20:01 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/06 10:23:01 by akhaliss         ###   ########.fr       */
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
