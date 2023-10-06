/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:41:26 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/06 10:56:12 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_break(void)
{
	ft_putendl_fd("\nexit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
void	syn_er(void)
{
	ft_putendl_fd("syntax error", STDOUT_FILENO);
	
}

void	voided(int ac, char **av)
{
	(void)av;
	(void)ac;
}


int	line_syntax(char *line)
{

	if (*line == '|')
	{
		stx_error();
		return (0);
	}
	while (*line)
	{
		while (v_spaces(*line))
			line++; 
		if ( !_pipe(&line) && !_redir(&line) && valid_quotes(&line) )
			line++;
		else
			return (stx_error(), 0);
	}
	return (1);
}

void	parse(char *line, t_envir **env, t_token **tmp, t_exec **mini)
{
	parsed_tok(tmp, line, env);
	to_exec(mini, tmp/*, env*/);
	// ft_execute(mini, env);	
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_envir	*_env;
	t_token	*tmp;
	t_exec	*mini;

	mini = NULL;
	tmp = NULL;
	voided(ac, av);
	_env = t_env(env);
	while (1)
	{
		line = ft_strtrim(readline("Minishell$ "), " \v\t\r\f");
		if (!line)
			t_break();
		add_history(line);
		if (line_syntax(line))
			parse(line, &_env, &tmp, &mini);
		free(line);
		free_token_list(&tmp);
		free_exec_list(&mini);
	}
	free_env(&_env);
	return (0);
}
