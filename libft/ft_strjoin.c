/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:34:36 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/07 21:23:29 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s = malloc(ft_strlen (s1) + ft_strlen(s2) + 1);
	if (!s)
		return (NULL);
	if ((s1[i] || s2[i]) != '\0')
	{
		while (s1[i])
			s[j++] = s1[i++];
		i = 0;
		while (s2[i])
			s[j++] = s2[i++];
	}
	s[j] = '\0';
	free(s1);
	free(s2);
	return (s);
}
