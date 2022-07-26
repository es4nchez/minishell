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
		return ;
	}
	else if (sig_nb == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
