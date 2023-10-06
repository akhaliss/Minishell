/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 08:44:52 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/06 10:56:40 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	cmd_size(t_token *line)
// {
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	if (!line)
// 		return(0);
// 	while (line && line->type != PIPE)
// 	{
// 		// i++;

// 		if (line->type == WORD)
// 			j++;
// 		else
// 			j += 2;
// 		line = line->next;
// 	}
// 	// return (i - j);
// 	return j;
// }

t_file		*_tmp(t_file *tmp)
{
	tmp = node_tmp(NULL);
	return (tmp);
}

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

char	**getTableOfCmd(t_token *line)
{	
	int size;
	char **cmd;

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

t_token		*prep_tmp(t_token *line, t_file *tmp/*, t_envir **env*/)
{
	int i = 0;
	tmp->cmd = getTableOfCmd(line);
	while (line && line->type != PIPE)
	{
		if (line->type != WORD)
			line = ft_files(line, tmp/*, env*/);
		else
		{
			tmp->cmd[i++] = ft_dup(line->word);
			line = line->next;
		}
	}
	tmp->cmd[i] = NULL;
	return (line);
}


void	to_exec(t_exec **line, t_token **parsed/*, t_envir **env*/)
{
	t_file	*tmp;
	t_token	*str;

	str = *parsed;
	while (str)
	{
		tmp = node_tmp(NULL);
		str = prep_tmp(str ,tmp/*, env*/);
		cmd_tolist(line, node_cmd(tmp->cmd, tmp->inf, tmp->outf));
		free(tmp);
		if (str && str->type == PIPE)
			str = str->next;
		else
			return ;		
	}
}
