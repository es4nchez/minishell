/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:03:43 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 12:51:31 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_w(t_input *input)
{
	close(input->pipe_fd[1]);
	dup2(input->pipe_fd[0], STDIN_FILENO);
	ft_close(input->pipe_fd[0]);
}

void	pipe_r(t_input *input)
{
	close(input->pipe_fd[0]);
	dup2(input->pipe_fd[1], STDOUT_FILENO);
	ft_close(input->pipe_fd[1]);
}
