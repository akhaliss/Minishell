/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:57:38 by akhaliss          #+#    #+#             */
/*   Updated: 2022/11/16 09:57:48 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;
	int	i;

	i = 0;
	l = ft_strlen(s);
	while (i <= l)
	{
		if (s[l] == (char)c)
			return ((char *) &s[l]);
			l--;
	}
	return (NULL);
}
