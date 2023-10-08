/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhaliss <akhaliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:41:26 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 17:44:56 by akhaliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_token **line, char *str, t_envir **env, size_t *i)
{
	t_type	token;

	token = tokens(str[*i], str[*i + 1]);
	if (token == HEREDOC)
		ft_heredoc(line, str, token, i);
	else if (token == APPEND)
		ft_append(line, token, i);
	else if (token == OUT)
		ft_out(line, token, i);
	else if (token == IN)
		ft_in(line, token, i);
	else if (token == PIPE)
		ft_pipe(line, token, i);
	else if (token == WORD)
		ft_word(line, str, env, i);
}

void	parsed_tok(t_token **line, char *str, t_envir **env)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] && v_spaces(str[i]))
			i++;
		parsing(line, str, env, &i);
	}
}

void	parse(char *line, t_envir **env, t_token **tmp, t_exec **mini)
{
	int	exit_status;

	exit_status = 0;
	parsed_tok(tmp, line, env);
	to_exec(mini, tmp/*, env*/);
	ft_execute(env, *mini, &exit_status);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_envir	*_env;
	t_token	*tmp;
	t_exec	*mini;

	voided(ac, av);
	_env = t_env(env);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		mini = NULL;
		tmp = NULL;
		ft_signal();
		// rl_catch_signals = 0;
		line = ft_strtrim(readline("Minishell$ "), " \v\t\r\f");
		if (!line)
			t_break();
		if (ft_strlen(line))
			add_history(line);
		if (line_syntax(line))
			parse(line, &_env, &tmp, &mini);

		free_token_list(tmp);
		free_exec_list(mini);
		free(line);
	}
	free_env(&_env);
	return (0);
}
