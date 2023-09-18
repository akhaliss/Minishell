#include "minishell.h"

void	stx_error(void)
{
	ft_putendl_fd("Minishell : syntax error", 2);
	// g_gb.exit_stat = 258;
}