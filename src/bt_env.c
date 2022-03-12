#include "minishell.h"

void    bt_env(char **envp)
{
    int i;

    i = -1;
    while (envp[++i])
        ft_putendl_fd(envp[i], 1);
}