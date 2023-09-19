#include "minishell.h"

void t_break(void)
{
    ft_putendl_fd("\nexit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	voided(int ac, char **av)
{
	(void)av;
    (void)ac;
}

int	line_syntax(char *line)
{
	int i;

	i = 0;
	while(v_spaces(line[i]))
		(i)++;
	if (_redir(line) || !valid_quotes(line) || f_pipe(line) || invalid_doll(line))
	{
		stx_error();
		return (0);		
	}
	return (1);
}

t_exec	*parse(char *line)
{
	char	*str;
	t_token	**token;

	str = ft_strtrim(line, " \v\t\r\f");
	free(line);
	if (str)
	{
		if (!line_syntax(str))
			return (free(str), NULL);
		tokenize_input(str, token);
		// I could parse here by doing like that "parse(str);"
		
		
	}

}

int main(int ac, char **av, char **env)
{
    char *line;
    t_exec *cmd;
    
	voided(ac, av);
    t_env(env);
    while (1)
    {
        line = readline("Minishell$ ");
        if (!line)
            t_break();
        add_history(line);
		// if (line_syntax(line))
		// 	printf("suceess\n");
		cmd = parse(line);

    }
    
    return 0;
}
