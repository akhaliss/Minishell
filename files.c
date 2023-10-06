/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 08:32:24 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/05 18:46:48 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_files(t_file *fd, char *cmp, char *redir)
{
	if (_compar(">>", cmp))
	{
		if (fd->outf != -1)
			close(fd->outf);
		fd->outf = open(redir, O_CREAT | O_APPEND | O_WRONLY, 0644);		
	}
	else if (_compar(">", cmp))
	{
		if (fd->outf != -1)
			close(fd->outf);
		fd->outf = open(redir, O_CREAT | O_TRUNC | O_WRONLY , 0644);
	}
	else if (_compar("<", cmp))
	{
		if (fd->inf != -1)
			close(fd->inf);
		fd->inf = open(redir, O_RDONLY);
	}
}

t_token	*ft_files(t_token *line, t_file *tmp/*, t_envir **env*/)
{
    if (line && (line->type == APPEND || line->type == IN || line->type == OUT))
    {
        m_files(tmp, line->word, line->next->word);
        line = line->next;
    }
    // else if (line->type == HEREDOC)
    // {

    // }
    return (line);
}
