#include "minishell.h"

// void	child_process(char *argv, char **envp)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) == -1)
// 		error();
// 	pid = fork();
// 	if (pid == -1)
// 		error();
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		execute(argv, envp);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// }

// void    pipe_process(t_input *input)
// {
//     int in;
//     int out;

    
// 	while (i < argc - 2)
// 		child_process(argv[i++], envp);

// }