/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkace <abelkace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:41:26 by akhaliss          #+#    #+#             */
/*   Updated: 2023/10/08 19:54:28 by abelkace         ###   ########.fr       */
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

void print_exec(t_exec *e)
{
	int i = 0;
	while (e->cmd[i])
		printf("%s - ", e->cmd[i++]);
	printf("\n%d\n", e->in_fd);
	printf("%d\n", e->out_fd);
	printf("%p\n", e->next);
	printf("%p\n", e->prev);
}

void	parse(char *line, t_envir **env, t_token **tmp, t_exec **mini)
{
	int	exit_status;

	exit_status = 0;
	parsed_tok(tmp, line, env);
	to_exec(mini, tmp/*, env*/);
	// t_exec *t = *mini;
	// while (t) {
	// 	print_exec(t);
	// 	printf("-------------\n");
	// 	t = t->next;
	// }
	ft_execute(env, *mini, &exit_status);
}

// void lek(void)
// {
// 	system("leaks minishel");
// }

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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// atexit(lek);
		ft_signal();
		// rl_catch_signals = 0;
		line = readline("Minishell$ ");
		line = ft_strtrim(line, " \v\t\r\f");
		if (!line)
			t_break();
		add_history(line);
		if (line_syntax(line))
		{
			parse(line, &_env, &tmp, &mini);
		}
		free_token_list(&tmp);
		free_exec_list(&mini);
		free(line);
	}
	free_env(&_env);
	return (0);
}
