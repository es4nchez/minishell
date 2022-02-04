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
	if (sig_nb == SIGQUIT)
		exit (0);
	else if (sig_nb == SIGINT)
		return ;
}
