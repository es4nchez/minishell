/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:25:56 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:26:18 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	reset_std(t_input *input)
{
	dup2(input->fd_io[1], STDOUT_FILENO);
	dup2(input->fd_io[0], STDIN_FILENO);
}

void	close_fds(t_input *input)
{
	ft_close(input->pipe_fd[0]);
	ft_close(input->pipe_fd[1]);
}
