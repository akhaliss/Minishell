/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:20:58 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/05 18:05:20 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s01;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (start + len > ft_strlen(s))
		len--;
	s01 = malloc((sizeof(char)) * (len + 1));
	if (!s01)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		s01[i] = s[start];
		i++;
		start++;
	}
	s01[i] = '\0';
	return (s01);
}
