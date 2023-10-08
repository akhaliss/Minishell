/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:43:51 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/06 18:44:03 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr1(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*p;

	i = 0;
	if (!s)
		return (0);
	l = ft_strlen(s);
	if (start >= l)
		return (ft_strdup(""));
	if (len > l)
		len = l;
	if (len > l - start)
		len = l - start;
	p = (char *)malloc(len * sizeof(char) + 1);
	if (!p)
		return (0);
	while (i < len && start < l)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
