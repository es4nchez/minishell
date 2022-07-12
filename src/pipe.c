#include "minishell.h"

int heredoc_listener(char *delimiter, int fd_out)
{
	char	*str;

	if (!delimiter)
		return (1);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!str)
			return (1);
		if (!ft_strncmp(str, delimiter, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, fd_out);
		ft_putstr_fd("\n", fd_out);
        free(str);
	}
	free(str);
	return (0);
}

int heredoc(t_lstcmd *cmd)
{
	int	fd_io[2];

    if (pipe(fd_io))
	{
		perror("minishell: pipe: ");
		return (-1);
	}
    if (heredoc_listener(cmd->next->cmd, fd_io[1]))
		return (-1);
	close(fd_io[1]);
	return (fd_io[0]);
}

int fd_process(int redi, t_lstcmd *cmds)
{
    int fd;

    if (redi == 1 && cmds->next->next)
    {
        fd = open(cmds->next->next->cmd, O_RDONLY);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 2 && cmds->next->next)
    {
        fd = heredoc(cmds->next);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 3 && cmds->next->next)
    {
        fd = open(cmds->next->next->cmd,  O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 4 && cmds->next->next)
    {
        fd = open(cmds->next->next->cmd, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 5 && cmds->next->next)
    {
        
    }
    return (0);
}

int check_redirect(t_lstcmd *cmds)
{
    if (cmds->next)
    {
        if (!ft_strncmp(cmds->next->cmd, "<<", 3))
            return (2);
        if (!ft_strncmp(cmds->next->cmd, "<", 2))
            return (1);
        if (!ft_strncmp(cmds->next->cmd, ">>", 3))
            return (4);
        if (!ft_strncmp(cmds->next->cmd, ">", 2))
            return (3);
        if (!ft_strncmp(cmds->next->cmd, "|", 2))
            return (5);
    }
    else
        return (-1);
    return (0);
}
