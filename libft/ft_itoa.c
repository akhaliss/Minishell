/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:14:10 by akhaliss          #+#    #+#             */
/*   Updated: 2022/11/13 19:57:31 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= (-1);
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nm;
	int		ln;

	nm = n;
	if (nm == 0)
		return (ft_strdup("0"));
	ln = len(nm) + 1;
	str = malloc((sizeof(char)) * (ln));
	if (!str)
		return (NULL);
	ln--;
	str[ln] = '\0';
	if (nm < 0)
	{
		nm *= (-1);
		str[0] = '-';
	}
	ln--;
	while (nm > 0)
	{
		str[ln--] = (nm % 10) + '0';
		nm /= 10;
	}
	return (str);
}
