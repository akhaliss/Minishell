#include"minishell.h"

void	ft_env(t_exec *node)
{
	t_env	*env;

	env = g_gl.env;
	if (node->cmd[1])
	{
		write(2,"env: ", 5);
		ft_putstr(node->cmd[1], 2);
		write(2, ": No such file or directory\n", 28);
		return ;
	}
	while (env->link)
	{
		ft_putstr(env->var, node->out_fd);
		write(node->out_fd, "=", 1);
		ft_putstr(env->value, node->out_fd);
		write(node->out_fd, "\n", 1);
		env = env->link;
	}
}