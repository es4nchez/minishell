/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esanchez <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:54:20 by esanchez          #+#    #+#             */
/*   Updated: 2022/01/28 16:54:21 by esanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl(int	sig_nb)
{
	printf("signal nb : %d", sig_nb);
	if (sig_nb == 20)
		exit (0);
	else if (sig_nb == 2)
		printf("\n");
	return ;
}
