/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:24:05 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/01 12:49:25 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s01;
	int		i;

	i = 0;
	s01 = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s01)
		return (NULL);
	if (!s1)
		return (NULL);
	while (s1[i])
	{
		s01[i] = s1[i];
		i++;
	}
	s01[i] = '\0';
	return (s01);
}
