/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_ftsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:30:37 by abelkace          #+#    #+#             */
/*   Updated: 2023/10/06 15:31:35 by abelkace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	**free_all(char **p, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static int	count_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**aft_split(char *s, char c)
{
	int		i;
	char	**p;
	int		j;

	if (s == NULL)
		return (NULL);
	p = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!p)
		return (0);
	j = 0;
	i = 0;
	while (j < count_word(s, c))
	{
		while (s[i] == c)
			i++;
		p[j] = ft_substr(s, i, count_len(s + i, c));
		if (!p[j])
			return (free_all(p, j));
		i += count_len(s + i, c);
		j++;
	}
	p[j] = NULL;
	return (p);
}
