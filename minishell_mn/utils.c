#include "minishell.h"

int	v_spaces(char l)
{
	return (l == ' ' || l == '\v' || l == '\f'
		|| l == '\t' || l == '\r');
}

int	v_dollars(int l)
{
	return (ft_isalnum(l) || l == '_');
}

int skip_(char *line) 
{
    int i = 0;

    while (line[i] != '\0' && v_spaces(line[i]) && line[i] != '$')
        i++;
    if (line[i] == '$')
        return (i);
    return (0);
}
