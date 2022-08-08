/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:54:20 by esanchez          #+#    #+#             */
/*   Updated: 2022/07/22 14:31:19 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl(int sig_nb)
{
	if (sig_nb == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_retcmd = 1;
		return ;
	}
}

void	handle_signals2(int signo)
{
	if (signo == SIGINT)
	{
		ft_putendl_fd("", 1);
		g_retcmd = 128 + signo;
	}
	if (signo == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 1);
		rl_on_new_line();
		g_retcmd = 128 + signo;
	}
}

void	handle_herdoc(int signo)
{
	if (signo == SIGINT)
	{
		exit(128 + signo);
		g_retcmd = 128 + signo;
	}
	if (signo == SIGQUIT)
		return ;
}
