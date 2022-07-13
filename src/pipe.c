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

int heredoc(t_lstredi *redis)
{
	int	fd_io[2];

    if (pipe(fd_io))
	{
		perror("minishell: pipe: ");
		return (-1);
	}
    if (heredoc_listener(redis->file, fd_io[1]))
		return (-1);
	close(fd_io[1]);
	return (fd_io[0]);
}

void    pipe_w(t_input *input)
{
	close(input->pipe_fd[1]);
	dup2(input->pipe_fd[0], STDIN_FILENO);
}

void    pipe_r(t_input *input)
{
	close(input->pipe_fd[0]);
    dup2(input->pipe_fd[1], STDOUT_FILENO);
}

int fd_process(int redi, t_lstredi *redis, int out)
{
    int fd;
    int fd_temp;

    if (redi == 1 && redis)
    {
        fd = open(redis->file, O_RDONLY);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 2 && redis)
    {
        fd_temp = dup(STDOUT_FILENO);
        dup2(out, STDOUT_FILENO);
        fd = heredoc(redis);
        dup2(fd_temp, STDOUT_FILENO);
        if (dup2(fd, STDIN_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 3 && redis)
    {
        fd = open(redis->file,  O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (1);
        close(fd);
    }
    else if (redi == 4 && redis)
    {
        fd = open(redis->file, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (dup2(fd, STDOUT_FILENO) == -1)
            return (1);
        close(fd);
    }
    return (0);
}

int check_redirect(t_lstredi *redis)
{
    if (redis != NULL)
    {
        if (redis->redi && !ft_strncmp(redis->redi, "<<", 3))
            return (2);
        if (redis->redi && !ft_strncmp(redis->redi, "<", 2))
            return (1);
        if (redis->redi && !ft_strncmp(redis->redi, ">>", 3))
            return (4);
        if (redis->redi && !ft_strncmp(redis->redi, ">", 2))
            return (3);
    }
    else
        return (-1);
    return (0);
}
