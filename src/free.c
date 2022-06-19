#include "minishell.h"

void    free_input(t_input *input)
{
    if (input->lineread)
        ft_cmdclear(&(input->cmds), free);
    free(input->lineread);
    free(input);
}