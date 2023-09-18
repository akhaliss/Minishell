#include "minishell.h"

int	f_pipe(char *line)
{
	int	i;

	i = -1;
	if (line[0] == '|')
		return (1);
	while (line[++i])
	{
		if (v_spaces(line[i]))
			i++;
		else
			break;
	}
	if (line[i] == '|')
		return (1);
	return (0);
}

int next_quote(char *line, int i, int *nq, int q)
{
    int j;

	j = i;
    *nq += 1;
    while (line[++j])
	{
        if (line[j] == q)
		{
            *nq += 1;
            break ;
        }
    }
    return (j - i);
}

int valid_quotes(char *line)
{
    int	i;
    int	s;
    int	d;
    
	i = -1;
	s = 0;
	d = 0;
    while (line[++i])
	{
        if (line[i] == 34)
            i += next_quote(line, i, &d, 34);
		else if (line[i] == 39)
            i += next_quote(line, i, &s, 39);
    }
    if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
        return (0);
    return (1);
}

int	_redir(char *line)
{
    int	i;

    i = -1;
	while (line[++i]) 
	{
        if (line[i] == '<' || line[i] == '>')
		{
            if (line[i] == line[i + 1])
                i += 2;
            i++;
            while (line[i] && v_spaces(line[i]))
                i++;
            if (line[i] == '|' || line[i] == '<' || line[i] == '>' || !line[i] )
                return (1);
        }
        i++;
    }
    return (0);
}

int invalid_doll(char *line)
{
    int i;

    if (skip_(line))
        i = skip_(line);
    while (line[++i])
    {
        if (v_spaces(line[i]))
            i++;
        else if (ft_strchr("<>", line[i + 1]))
            return (1);
    }
    return (0);
}
