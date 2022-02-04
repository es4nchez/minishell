/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_threading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:55:09 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/28 13:55:12 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exist(char *cmd)
{
	char	*bin;
	struct stat	buff;

	bin = ft_strjoin("/bin/", cmd);
	if (stat(bin, &buff) == -1)
		return (0);
	else
		return (1);
}

void	cmd_not_found(char *cmd)
{
	printf("mishellout: command not found: %s\n", cmd);
}

void	execve_threading(char *cmd, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	if (cmd_exist(argv[0]) == 0)
	{
		cmd_not_found(argv[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Forking Error\n");
		return ;
	}
	else if (pid == 0)
	{
		printf("\e[31mcmd :\e[32m %s %s\e[0m\n", cmd, argv[1]);
		execve(cmd, &argv[0], envp);
		return ;
	}
	else
		wait(&status);
	return ;
}
