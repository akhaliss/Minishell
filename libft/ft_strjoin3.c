/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:25:15 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/06 22:45:26 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin3(char const *s1, char const *s2, const char *s3)
{
	int		len1;
	int		len2;
	int		len3;
	char	*s;

	if (!s1 || !s2 || !s3)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen (s2);
	len3 = ft_strlen(s3);
	s = (char *)malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	if (!s)
		return (0);
	ft_memcpy(s, s1, len1);
	ft_memcpy(s + len1, s2, len2);
	ft_memcpy(s + len1 + len2, s3, len3);
	s[len1 + len2 + len3] = '\0';
	return (s);
}
