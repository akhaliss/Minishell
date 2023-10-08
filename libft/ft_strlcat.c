/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:56:56 by akhaliss          #+#    #+#             */
/*   Updated: 2022/11/13 19:45:44 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	destl;
	size_t	srcl;
	size_t	l;

	srcl = ft_strlen(src);
	if (dst == 0 && dstsize == 0)
		return (srcl);
	destl = ft_strlen(dst);
	l = destl + srcl;
	i = 0;
	if (dstsize == 0 || (dstsize <= destl))
		return (srcl + dstsize);
	else if (dstsize > destl)
	{
		while (src[i] && destl < (dstsize - 1) && dstsize != 0)
		{
			dst[destl] = src[i];
			destl++;
			i++;
		}
	}
	dst[destl] = '\0';
	return (l);
}
