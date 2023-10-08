/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:44:52 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 15:11:55 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_file	*_tmp(t_file *tmp)
// {
// 	tmp = node_tmp(NULL);
// 	return (tmp);
// }

char	*ft_dup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len + 1);
	return (str);
}

char	**get_table(t_token *line)
{
	int		size;
	char	**cmd;

	cmd = NULL;
	size = 0;
	while (line && line->type != PIPE)
	{
		if (line->type == WORD)
			size++;
		line = line->next;
	}
	if (size)
	{
		cmd = malloc(sizeof(char *) * (size + 1));
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_token	*prep_tmp(t_token *line, t_exec *tmp/*, t_envir **env*/)
{
	int	i;
	
	i = 0;
	tmp->in_fd = 0;
	tmp->out_fd = 1;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->cmd = get_table(line);
	while (line && line->type != PIPE)
	{
		if (line->type != WORD)
			line = ft_files(line, tmp/*, env*/);
		else
		{
			if (line)
				tmp->cmd[i++] = ft_dup(line->word);
			if ((line->next && line->next->type == PIPE) || (!line->next))
				tmp->cmd[i] = NULL;
		}
		line = line->next;
	}
	return (line);
}

void	to_exec(t_exec **line, t_token **parsed/*, t_envir **env*/)
{
	t_token	*str;
	t_exec *node;

	str = *parsed;
	while (str)
	{
		// tmp = node_tmp(NULL);
		node = malloc(sizeof(t_exec));
		if (!node)//TODO
			return ;
		str = prep_tmp(str, node/*, env*/);
		cmd_tolist(line, node);
		if (str && str->type == PIPE)
			str = str->next;
		// else
		// 	return ;
	}
}