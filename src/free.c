#include "minishell.h"

void    free_input(t_input *input)
{
    ft_lstclear(&(input->lst), free);
    free(input->lineread);
    free(input);
}