/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:54:20 by esanchez          #+#    #+#             */
/*   Updated: 2022/02/04 16:20:39 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl(int	sig_nb)
{
	rl_replace_line("", 0);
	ft_putendl_fd("", 1);
	if (sig_nb == SIGQUIT)
		exit (0);
	else if (sig_nb == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
