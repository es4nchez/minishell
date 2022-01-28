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

void	execve_threading(char *cmd, char **argv, char **envp)
{
	pid_t pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		printf("Error1");
		return ;
	}
	else if (pid == 0)
	{
		execve(cmd, argv, envp);
		return ;
	}
	else
		wait(&status);
	return ;
}
