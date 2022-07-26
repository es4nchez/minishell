/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalthaus <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 14:26:53 by yalthaus          #+#    #+#             */
/*   Updated: 2022/07/22 14:37:59 by yalthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input(t_input *input)
{
	if (input->lineread)
		ft_cmdclear(&(input->cmds), free);
	free(input->lineread);
	free(input);
	exit(0);
}
