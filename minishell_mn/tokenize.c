#include "minishell.h"

t_token *tokenize_input(char *input)
{
    t_token *head;
    t_token *token;
    t_type  tok;
    char    *word;
    
    head = NULL;
    word = ft_strtrim(input, " \t\v\r\f");
    free(input);
    while (word)
    {
        if (ft_strcmp(word, "<<") == 0)
            tok = HEREDOC;
        else if (ft_strcmp(word, ">>") == 0)
            tok = APPEND;
        else if (ft_strcmp(word, ">") == 0)
            tok = OUT;
        else if (ft_strcmp(word, ">") == 0)
            tok = OUT;
        else if (ft_strcmp(word, "|") == 0)
            tok = PIPE;
        else
    		tok = WORD;
        token = node_token(word, tok);
        token_tolist(&head, token);
    }
    free(word);
    return (head);
}
