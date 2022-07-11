#include "minishell.h"


int fd_process(int redi, int fd_io[], t_lstcmd *cmds)
{
    int fd;

    (void)fd_io;

    if (redi == 1 && cmds->next->next)
    {
        fd = open(cmds->next->next->cmd, O_RDONLY);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (1);
    }
    return (0);
}

int check_redirect(t_lstcmd *cmds)
{
    if (cmds->next)
    {
        if (!ft_strncmp(cmds->next->cmd, "<", 1))
            return (1);
        if (!ft_strncmp(cmds->next->cmd, "<<", 2))
            return (2);
        if (!ft_strncmp(cmds->next->cmd, ">", 1))
            return (3);
        if (!ft_strncmp(cmds->next->cmd, ">>", 2))
            return (4);
        if (!ft_strncmp(cmds->next->cmd, "|", 1))
            return (5);
    }
    else
        return (-1);
    return (0);
}
