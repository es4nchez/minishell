#include "minishell.h"

void	bt_exit(t_input *input)
{
	free_input(input);
	ft_putendl_fd("exit", 1);
	exit(0);
}
